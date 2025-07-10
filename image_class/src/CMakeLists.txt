project(image_class LANGUAGES C ASM)

# List source files to be compiled
add_executable(${PROJECT_NAME}
    # Benchmark files
    image_class/main.c
    image_class/tm_layers.c
    image_class/tm_model.c
    image_class/tm_stat.c

    # Other
    portme/printf.c
    portme/printfmap.c
    ${STARTUP_CODE}
    )

# Change target suffix
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ${OUTPUT_SUFFIX})

target_include_directories(${PROJECT_NAME}
       PUBLIC
       image_class
       portme
     )

target_link_libraries(${PROJECT_NAME}
    gcc
    c
    m
    )
