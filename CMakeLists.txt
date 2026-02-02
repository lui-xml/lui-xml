# Lui-XML CMake Build Configuration
# Lightweight User Interface XML - XML-based declarative UI for LVGL
# Derived from LVGL v9.1.0 XML subsystem

cmake_minimum_required(VERSION 3.16)
project(lui_xml
    VERSION 9.1.0
    DESCRIPTION "Lightweight User Interface XML - XML-based declarative UI for LVGL"
    LANGUAGES C
)

# Project information
set(PROJECT_NAME "Lui-XML")
set(PROJECT_DESCRIPTION "XML-based declarative UI library for LVGL v9.x")
set(PROJECT_URL "https://github.com/lui-xml/lui-xml")

# Version information
set(LUI_XML_VERSION_MAJOR 9)
set(LUI_XML_VERSION_MINOR 1)
set(LUI_XML_VERSION_PATCH 0)
set(LUI_XML_VERSION "${LUI_XML_VERSION_MAJOR}.${LUI_XML_VERSION_MINOR}.${LUI_XML_VERSION_PATCH}")
set(LUI_XML_SOVERSION 0)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# C standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

###############################################################################
# LVGL Dependency Detection
###############################################################################

message(STATUS "")
message(STATUS "Lui-XML v${LUI_XML_VERSION}")
message(STATUS "--------------")

# Try to find LVGL using various methods
set(LVGL_FOUND FALSE)

# Method 1: Check if LVGL target already exists
if(TARGET lvgl::lvgl)
    message(STATUS "  LVGL: Found (lvgl::lvgl target)")
    set(LVGL_TARGET lvgl::lvgl)
    set(LVGL_FOUND TRUE)
elseif(TARGET lvgl)
    message(STATUS "  LVGL: Found (lvgl target)")
    set(LVGL_TARGET lvgl)
    set(LVGL_FOUND TRUE)
endif()

# Method 2: Try find_package if LVGL_DIR is set
if(NOT LVGL_FOUND AND DEFINED LVGL_DIR)
    message(STATUS "  LVGL: Searching in ${LVGL_DIR}")
    set(CMAKE_PREFIX_PATH ${LVGL_DIR} ${CMAKE_PREFIX_PATH})
    find_package(lvgl QUIET)
    if(lvgl_FOUND)
        message(STATUS "  LVGL: Found via find_package")
        set(LVGL_TARGET lvgl::lvgl)
        set(LVGL_FOUND TRUE)
    endif()
endif()

# Method 3: Try config mode
if(NOT LVGL_FOUND)
    find_package(lvgl QUIET CONFIG)
    if(lvgl_FOUND)
        message(STATUS "  LVGL: Found via CONFIG")
        # Determine the target name
        if(TARGET lvgl::lvgl)
            set(LVGL_TARGET lvgl::lvgl)
        elseif(TARGET lvgl)
            set(LVGL_TARGET lvgl)
        endif()
        set(LVGL_FOUND TRUE)
    endif()
endif()

# Fatal error if LVGL not found
if(NOT LVGL_FOUND)
    message(FATAL_ERROR
        "Lui-XML requires LVGL v9.x but LVGL was not found.\n"
        "Please ensure LVGL is available by one of these methods:\n"
        "  1. Include LVGL before Lui-XML in your CMakeLists.txt\n"
        "  2. Set LVGL_DIR to point to LVGL installation\n"
        "  3. Install LVGL in a standard location"
    )
endif()

message(STATUS "  LVGL target: ${LVGL_TARGET}")

###############################################################################
# Version Detection
###############################################################################

# Try to extract LVGL version from target or config
# Note: This is best-effort. The actual version check happens at compile-time
# in luixml_compat.h via the #error directives.

set(LVGL_VERSION detected)

# Try to get version from lvgl config if available
if(DEFINED LVGL_VERSION_MAJOR)
    set(LVGL_VERSION "${LVGL_VERSION_MAJOR}.${LVGL_VERSION_MINOR}.${LVGL_VERSION_PATCH}")
    message(STATUS "  LVGL version: ${LVGL_VERSION}")

    # Version compatibility check (support v9.0+)
    if(LVGL_VERSION_MAJOR VERSION_LESS 9)
        message(FATAL_ERROR
            "Lui-XML v${LUI_XML_VERSION} requires LVGL v9.0 or later.\n"
            "Detected LVGL v${LVGL_VERSION}."
        )
    elseif(LVGL_VERSION_MAJOR EQUAL 9 AND LVGL_VERSION_MINOR VERSION_GREATER 5)
        message(WARNING
            "Lui-XML is compatible with LVGL v9.x.\n"
            "Detected LVGL v${LVGL_VERSION}. Compatibility not guaranteed."
        )
    endif()
else()
    message(WARNING
        "Lui-XML: Could not detect LVGL version.\n"
        "Compile-time checks will validate compatibility."
    )
endif()

###############################################################################
# Lui-XML Source Files
###############################################################################

# Compatibility layer sources
set(LUI_XML_COMPAT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/luixml_compat.c
)

# All XML source files (extracted from LVGL)
file(GLOB_RECURSE LUI_XML_XML_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/xml/*.c"
)

# Complete source list
set(LUI_XML_SOURCES
    ${LUI_XML_COMPAT_SOURCES}
    ${LUI_XML_XML_SOURCES}
)

# Add defines for conditional compilation
add_definitions(-DLV_USE_XML=1)

###############################################################################
# Lui-XML Library Target
###############################################################################

# Create interface library (header-only plus extracted sources)
add_library(lui_xml INTERFACE)

# Add alias for consistency with LVGL naming
add_library(lui::xml ALIAS lui_xml)

# Include directories
target_include_directories(lui_xml
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/xml
)

# Source files (for IDE projects and consistency)
target_sources(lui_xml
    INTERFACE
        ${LUI_XML_SOURCES}
)

# Link against LVGL
target_link_libraries(lui_xml
    INTERFACE
        ${LVGL_TARGET}
)

###############################################################################
# Build Summary
###############################################################################

message(STATUS "")
message(STATUS "Lui-XML configuration complete:")
message(STATUS "  Version: ${LUI_XML_VERSION}")
message(STATUS "  Sources: ${LUI_XML_SOURCES}")
message(STATUS "  Target: lui::xml")
message(STATUS "  LVGL dependency: ${LVGL_TARGET}")
if(DOXYGEN_FOUND)
    message(STATUS "  Documentation: make docs (to generate API docs)")
endif()
message(STATUS "")

# Export the library for find_package()
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR})
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR})

# Installation rules
install(
    DIRECTORY src/
    DESTINATION ${INCLUDE_INSTALL_DIR}/lui_xml
    FILES_MATCHING PATTERN "*.h"
)

install(
    FILES
        ${CMAKE_CURRENT_CURRENT_BINARY_DIR}/lui_xmlConfig.cmake
        ${CMAKE_CURRENT_CURRENT_BINARY_DIR}/lui_xmlConfigVersion.cmake
    DESTINATION ${LIB_INSTALL_DIR}/cmake/lui_xml
)

###############################################################################
# Documentation Target (Phase 5)
###############################################################################

# Add a custom target to generate documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs)

    add_custom_target(docs
        COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUT}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )

    message(STATUS "  Doxygen: Found (run 'make docs' to generate API documentation)")
else()
    message(STATUS "  Doxygen: Not found (documentation generation disabled)")
    # Create a placeholder target
    add_custom_target(docs
        COMMAND ${CMAKE_COMMAND} -E echo "Doxygen not found. Cannot generate documentation."
    )
endif()

