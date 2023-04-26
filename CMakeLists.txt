CMAKE_MINIMUM_REQUIRED(VERSION 3.3.0)
set(my_tty "mytty")


link_directories(
#${CMAKE_SYSROOT}/cjson
${PROJECT_BINARY_DIR}/cjson
)

aux_source_directory(. SOURCE_DIR)
add_subdirectory(cjson)
add_executable(${my_tty} mytty.c parser.c c_serial.c)
add_dependencies(${my_tty} cJSON)
target_link_libraries(${my_tty} -lpthread libcJSON.a)
