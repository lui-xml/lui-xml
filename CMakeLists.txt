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
set(PROJECT_DESCRIPTION "XML-based declarative UI library for LVGL v9.1.0")
set(PROJECT_URL "https://github.com/lui-xml/lui-xml")

# Version information
set(LUI_XML_VERSION_MAJOR 9)
set(LUI_XML_VERSION_MINOR 1)
set(LUI_XML_VERSION_PATCH 0)
set(LUI_XML_VERSION "${LUI_XML_VERSION_MAJOR}.${LUI_XML_VERSION_MINOR}.${LUI_XML_VERSION_PATCH}")

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# C standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find LVGL dependency
# NOTE: LVGL v9.1.0 must be installed separately
# This is a stub - full CMake configuration will be implemented in Phase 3

message(STATUS "${PROJECT_NAME} v${LUI_XML_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Find LVGL dependency
# LVGL v9.0+ must be installed separately

# Try to find LVGL using standard methods
if(TARGET lvgl::lvgl)
    message(STATUS "  LVGL: Found (lvgl::lvgl target)")
    set(LVGL_FOUND TRUE)
elseif(DEFINED LVGL_DIR)
    # User specified LVGL directory
    set(CMAKE_PREFIX_PATH ${LVGL_DIR} ${CMAKE_PREFIX_PATH})
    find_package(lvgl REQUIRED)
    set(LVGL_FOUND TRUE)
else()
    message(WARNING "LVGL not found. Please set LVGL_DIR or ensure LVGL is installed.")
    set(LVGL_FOUND FALSE)
endif()

# Version check - require LVGL v9.0+
if(LVGL_FOUND AND TARGET lvgl::lvgl)
    # Version detection will be handled by compile-time checks in luixml_compat.h
    message(STATUS "  Lui-XML: Configuring for LVGL v9.x")
endif()

# Lui-XML source files (Phase 2: Compatibility Layer)
set(LUI_XML_COMPAT_SOURCES
    src/luixml_compat.c
)

# All XML source files (extracted from LVGL)
file(GLOB_RECURSE LUI_XML_XML_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/xml/*.c"
)

set(LUI_XML_SOURCES
    ${LUI_XML_COMPAT_SOURCES}
    ${LUI_XML_XML_SOURCES}
)

set(LUI_XML_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/xml
)

message(STATUS "  Lui-XML source files: ${LUI_XML_SOURCES}")
message(STATUS "  Lui-XML include dirs: ${LUI_XML_INCLUDE_DIRS}")

# TODO: Phase 3 - Create lui_xml library target
# TODO: Phase 3 - Add source files to target
file(GLOB_RECURSE LUI_XML_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.c"
)

file(GLOB_RECURSE LUI_XML_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
)

message(STATUS "Found ${LUI_XML_SOURCES} source files")
message(STATUS "Found ${LUI_XML_HEADERS} header files")

# NOTE: This is a stub only. Do not use for building yet.
# Phase 3 will implement the complete build system.
