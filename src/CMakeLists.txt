include_directories(${PROJECT_SOURCE_DIR}/inc)

set(APP_SRC t_main.c debug.c)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(SRC_LIB dc_sort.c heap_sort.c)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(lib_sort ${SRC_LIB})
add_executable(test ${APP_SRC})

TARGET_LINK_LIBRARIES(test lib_sort)
