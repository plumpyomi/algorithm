include_directories(${PROJECT_SOURCE_DIR}/inc)

set(APP_SRC t_main.c debug.c)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_library(libdc_sort dc_sort.c)
add_executable(test ${APP_SRC})
