project(lzfx_comp LANGUAGES C ASM)

# List source files to be compiled
add_executable(${PROJECT_NAME}
    # Benchmark files
    lzfx_comp/lzfx.c
    lzfx_comp/lzfx_compress_test.c

    # Other
    portme/printf.c
    portme/printfmap.c
    ${STARTUP_CODE}
    )

# Change target suffix
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ${OUTPUT_SUFFIX})

target_include_directories(${PROJECT_NAME}
       PUBLIC
       lzfx_comp
       portme
     )

target_link_libraries(${PROJECT_NAME}
    gcc
    c
    m
    )
