project(lorawan_down LANGUAGES C ASM)

# List source files to be compiled
add_executable(${PROJECT_NAME}
    # Benchmark files
    lorawan_down/aes.c
    lorawan_down/cmac.c
    lorawan_down/inputs.c
    lorawan_down/lorawan_down_test.c
    lorawan_down/lw.c

    # Other
    portme/printf.c
    portme/printfmap.c
    ${STARTUP_CODE}
    )

# Change target suffix
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ${OUTPUT_SUFFIX})

target_include_directories(${PROJECT_NAME}
       PUBLIC
       lorawan_down
       portme
     )

target_link_libraries(${PROJECT_NAME}
    gcc
    c
    m
    )
