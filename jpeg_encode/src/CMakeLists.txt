project(jpeg_encode LANGUAGES C ASM)

# List source files to be compiled
add_executable(${PROJECT_NAME}
    # Benchmark files
    jpeg_encode/buf.c
    jpeg_encode/conf.c
    jpeg_encode/enc.c
    jpeg_encode/huff.c
    jpeg_encode/jpeg_encode_test.c

    # Other
    portme/printf.c
    portme/printfmap.c
    ${STARTUP_CODE}
    )

# Change target suffix
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ${OUTPUT_SUFFIX})

target_include_directories(${PROJECT_NAME}
       PUBLIC
       jpeg_encode
       portme
     )

target_link_libraries(${PROJECT_NAME}
    gcc
    c
    m
    )
