project(mp3_encode LANGUAGES C ASM)

# List source files to be compiled
add_executable(${PROJECT_NAME}
    # Benchmark files
    mp3_encode/mp3_encode_test.c
    mp3_encode/shine_mp3.c

    # Other
    portme/printf.c
    portme/printfmap.c
    ${STARTUP_CODE}
    )

# Change target suffix
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ${OUTPUT_SUFFIX})

target_include_directories(${PROJECT_NAME}
       PUBLIC
       mp3_encode
       portme
     )

target_link_libraries(${PROJECT_NAME}
    gcc
    c
    m
    )
