
add_executable(sgemm main.cu)
target_include_directories(sgemm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/kernels)

