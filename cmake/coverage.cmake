# ------------------------------------------------------------------------------
# Copyright (c) 2025 Onur Tuncer, PhD, Istanbul Technical University
#
# SPDX-License-Identifier: MIT
# License-Filename: LICENSE
# ------------------------------------------------------------------------------

function(add_coverage_target exclude)

    find_program(GCOV gcov)
    if (NOT GCOV)
        message(WARNING "program gcov not found")
    endif()

    find_program(LCOV lcov)
    if (NOT LCOV)
        message(WARNING "program lcov not found")
    endif()

    find_program(GENHTML genhtml)
    if (NOT GENHTML)
        message(WARNING "program genhtml not found")
    endif()

    if (LCOV AND GCOV AND GENHTML)
        set(covname cov.info)
       
        add_custom_target(messagelogger_cov DEPENDS ${covname})

        add_custom_command(
            OUTPUT  ${covname}
            COMMAND ${LCOV} -c -o ${covname} -d . -b . --gcov-tool ${GCOV}  # Capture coverage data
            COMMAND ${LCOV} -r ${covname} ${exclude} -o ${covname}  # Exclude directories
            COMMAND ${LCOV} -l ${covname}  # List remaining coverage
            COMMAND ${GENHTML} ${covname} --output-directory coverage  # Generate HTML report
            COMMAND ${LCOV} -l ${covname} 2>/dev/null | grep Total | sed 's/|//g' | sed 's/Total://g' | awk '{print $1}' | sed s/%//g > coverage/total  # Extract total percentage
        )

        set_directory_properties(PROPERTIES
            ADDITIONAL_CLEAN_FILES ${covname}
        )
    else()
        message(WARNING "unable to add target `cov`: missing coverage tools")
    endif()

endfunction()
