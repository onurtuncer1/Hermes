# ------------------------------------------------------------------------------
# Copyright (c) 2025, Onur Tuncer, PhD, Istanbul Technical University
#
# SPDX-License-Identifier: MIT
# License-Filename: LICENSE
# ------------------------------------------------------------------------------

function(sanitizer_fail_test_on_error test_name)
    if(CMAKE_BUILD_TYPE MATCHES "AddressSanitizer")
        set_tests_properties(${test_name} PROPERTIES
            FAIL_REGULAR_EXPRESSION "ERROR: AddressSanitizer")
        set_tests_properties(${test_name} PROPERTIES
            FAIL_REGULAR_EXPRESSION "ERROR: LeakSanitizer")
    elseif(CMAKE_BUILD_TYPE MATCHES "MemorySanitizer")
        set_tests_properties(${test_name} PROPERTIES
            FAIL_REGULAR_EXPRESSION "WARNING: MemorySanitizer")
    elseif(CMAKE_BUILD_TYPE MATCHES "ThreadSanitizer")
        set_tests_properties(${test_name} PROPERTIES
            FAIL_REGULAR_EXPRESSION "WARNING: ThreadSanitizer")
    elseif(CMAKE_BUILD_TYPE MATCHES "UndefinedBehaviorSanitizer")
        set_tests_properties(${test_name} PROPERTIES
            FAIL_REGULAR_EXPRESSION "runtime error:")
    endif()
endfunction()
