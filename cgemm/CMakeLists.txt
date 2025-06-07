# cpu gemm
add_executable(cpugemm main.cc)
target_include_directories(cpugemm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/kernels)

