project(lorawan_up LANGUAGES C ASM)

# List source files to be compiled
add_executable(${PROJECT_NAME}
    # Benchmark files
    lorawan_up/aes.c
    lorawan_up/cmac.c
    lorawan_up/lorawan_up_test.c
    lorawan_up/lw.c

    # Other
    portme/printf.c
    portme/printfmap.c
    ${STARTUP_CODE}
    )

# Change target suffix
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ${OUTPUT_SUFFIX})

target_include_directories(${PROJECT_NAME}
       PUBLIC
       lorawan_up
       portme
     )

target_link_libraries(${PROJECT_NAME}
    gcc
    c
    m
    )
