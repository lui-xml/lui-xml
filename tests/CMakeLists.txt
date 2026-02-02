# Lui-XML Test Suite CMake Configuration

cmake_minimum_required(VERSION 3.16)

# Test project
enable_testing()

# Include Lui-XML source files
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/xml
)

# Find LVGL (required for tests)
if(NOT LVGL_FOUND)
    message(FATAL_ERROR "Tests require LVGL. Please set LVGL_DIR or ensure LVGL is available.")
endif()

# Add compiler flags for coverage
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(CodeCoverage)
    append_coverage_compiler_flags()
    set(COVERAGE_LCOV ON)
endif()

###############################################################################
# Test Utilities
#############################################################################

set(TESTUTIL_SOURCES
    test_utils.c
)

add_library(testutil STATIC ${TESTUTIL_SOURCES})
target_link_libraries(testutil ${LVGL_TARGET})

###############################################################################
# Unit Tests
#############################################################################

# Parser Tests
add_executable(test_parser_minimal
    test_parser_minimal.c
)
target_link_libraries(test_parser_minimal
    testutil
    ${LVGL_TARGET}
)
add_test(NAME test_parser_minimal COMMAND test_parser_minimal)

add_executable(test_parser_comprehensive
    test_parser_comprehensive.c
)
target_link_libraries(test_parser_comprehensive
    testutil
    ${LVGL_TARGET}
)
add_test(NAME test_parser_comprehensive COMMAND test_parser_comprehensive)

# Widget Tests
add_executable(test_widget_button
    test_widget_button.c
)
target_link_libraries(test_widget_button
    testutil
    ${LVGL_TARGET}
)
add_test(NAME test_widget_button COMMAND test_widget_button)

add_executable(test_widget_label
    test_widget_label.c
)
target_link_libraries(test_widget_label
    testutil
    ${LVGL_TARGET}
)
add_test(NAME test_widget_label COMMAND test_widget_label)

add_executable(test_widget_image
    test_widget_image.c
)
target_link_libraries(test_widget_image
    testutil
    ${LVGL_TARGET}
)
add_test(NAME test_widget_image COMMAND test_widget_image)

# Namespace Compliance Tests
add_executable(test_namespace_compliance
    test_namespace_compliance.c
)
target_link_libraries(test_namespace_compliance
    ${LVGL_TARGET}
)
add_test(NAME test_namespace_compliance COMMAND test_namespace_compliance)

###############################################################################
# Integration Tests
#############################################################################

add_executable(test_integration_simple_ui
    test_integration_simple_ui.c
)
target_link_libraries(test_integration_simple_ui
    testutil
    ${LVGL_TARGET}
)
add_test(NAME test_integration_simple_ui COMMAND test_integration_simple_ui)

###############################################################################
# Coverage Reporting
###############################################################################

if(COVERAGE_LCOV)
    # Setup coverage for all test executables
    SETUP_TARGET_FOR_COVERAGE_GCOV_LCOV(
        NAME test_coverage
        EXECUTABLES
            test_parser_minimal
            test_parser_comprehensive
            test_widget_button
            test_widget_label
            test_widget_image
            test_namespace_compliance
            test_integration_simple_ui
        BASEDIR ${CMAKE_SOURCE_DIR}
        EXCLUDE_DIRS
            /usr/*
            tests/*
    )
endif()

###############################################################################
# Valgrind Configuration
###############################################################################

find_program(VALGRIND valgrind)
if(VALGRIND)
    # Add Valgrind memcheck tests
    add_test(NAME test_parser_minimal_valgrind
        COMMAND ${VALGRIND}
            --leak-check=full
            --show-leak-kinds=all
            --error-exitcode=1
            --suppressions=${CMAKE_CURRENT_SOURCE_DIR}/valgrind.supp
            $<TARGET_FILE:test_parser_minimal>
    )

    add_test(NAME test_parser_comprehensive_valgrind
        COMMAND ${VALGRIND}
            --leak-check=full
            --show-leak-kinds=all
            --error-exitcode=1
            --suppressions=${CMAKE_CURRENT_SOURCE_DIR}/valgrind.supp
            $<TARGET_FILE:test_parser_comprehensive>
    )

    add_test(NAME test_integration_simple_ui_valgrind
        COMMAND ${VALGRIND}
            --leak-check=full
            --show-leak-kinds=all
            --error-exitcode=1
            --suppressions=${CMAKE_CURRENT_SOURCE_DIR}/valgrind.supp
            $<TARGET_FILE:test_integration_simple_ui>
    )

    # Set Valgrind tests to run in parallel
    set_tests_properties(test_parser_minimal_valgrind
                        test_parser_comprehensive_valgrind
                        test_integration_simple_ui_valgrind
        PROPERTIES
        RUN_SERIAL FALSE
    )
endif()

message(STATUS "")
message(STATUS "Test configuration complete:")
message(STATUS "  Unit tests: 6 test executables")
message(STATUS "  Integration tests: 1 test executable")
message(STATUS "  Coverage: ${COVERAGE_LCOV}")
message(STATUS "  Valgrind: ${VALGRIND_FOUND}")
message(STATUS "")
