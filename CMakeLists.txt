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

# TODO: Phase 3 - Implement full CMake configuration
# TODO: Phase 3 - Add LVGL dependency detection
# TODO: Phase 3 - Add version checking (LVGL v9.1.0 required)
# TODO: Phase 3 - Configure include directories
# TODO: Phase 3 - Add source files
# TODO: Phase 3 - Create lui_xml library target

# For now, just list the source files that exist
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
