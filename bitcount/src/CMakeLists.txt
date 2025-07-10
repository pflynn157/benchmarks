project(bitcount LANGUAGES C ASM)

# List source files to be compiled
add_executable(${PROJECT_NAME}
    # Benchmark files
    bitcount/bitcnt_1.c
    bitcount/bitcnt_2.c
    bitcount/bitcnt_3.c
    bitcount/bitcnt_4.c
    bitcount/bitstrng.c
    bitcount/bstr_i.c
    bitcount/main.c

    # Other
    portme/printf.c
    portme/printfmap.c
    ${STARTUP_CODE}
    )

# Change target suffix
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ${OUTPUT_SUFFIX})

target_include_directories(${PROJECT_NAME}
       PUBLIC
       bitcount
       portme
     )

target_link_libraries(${PROJECT_NAME}
    gcc
    c
    m
    )
