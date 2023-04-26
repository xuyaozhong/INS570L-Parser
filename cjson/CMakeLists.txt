file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

include_directories(
${CMAKE_SYSROOT}/usr/include
${PROJECT_BINARY_DIR}/include
)

link_directories(
${CMAKE_SYSROOT}/usr/lib64
${PROJECT_BINARY_DIR}/lib
)

set(lib_name "cJSON")
set(libutils_name "cJSON_Utils")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -ffunction-sections -fdata-sections") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -ffunction-sections -fdata-sections") 

aux_source_directory(. SOURCE_DIR)


add_library(${lib_name} cJSON.c)
add_library(${libutils_name} cJSON_Utils.c)


file(COPY ${HEADER_FILES} DESTINATION ${PROJECT_BINARY_DIR}/include)
