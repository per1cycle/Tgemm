cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(Tgemm LANGUAGES C CXX)

find_package(CUDAToolkit QUIET)

option(S "Enable SGEMM (CUDA)" ON)
option(H "Enable HGEMM (CUDA)" OFF)
option(C "Enable CGEMM (CPU fallback)" ON)

find_package(CUDAToolkit QUIET)
include_directories(${CMAKE_SOURCE_DIR})

if(CUDAToolkit_FOUND)
    # compared to class settings, we let NVidia's FindCUDA CMake detect 
    # whether to build x64.  We tell it to support most devices, though, 
    # to make sure more people can easily run class code without knowing 
    # about this compiler argument
    enable_language(CUDA)
    set(CUDA_NVCC_FLAGS "
    -ccbin /usr/bin/clang; 
    -gencode;arch=compute_30,code=sm_30;  
    -gencode;arch=compute_35,code=sm_35;
    -gencode;arch=compute_36,code=compute_35;
    -gencode;arch=compute_20,code=sm_20; 
    -gencode;arch=compute_11,code=sm_11; 
    -gencode;arch=compute_12,code=sm_12;
    -gencode;arch=compute_13,code=sm_13;")
    function(add_cublas TARGET SOURCE)
        add_executable(${TARGET} ${SOURCE})
        target_link_libraries(${TARGET} -lcublas -lcurand)
    endfunction(add_cublas)

    if (UNIX)
    	set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} "-Xcompiler -Wextra")
    	set(CMAKE_CXX_FLAGS "-stdlib=libstdc++")
    endif (UNIX)

    # add debugging to CUDA NVCC flags.  For NVidia's NSight tools.
    set(CUDA_NVCC_FLAGS_DEBUG ${CUDA_NVCC_FLAGS_DEBUG} "-G")
    set(CMAKE_CUDA_ARCHITECTURES 50 52 60 61 70 72 75 80 86 87 89 90)

	if(S)
		add_subdirectory(sgemm)
	endif(S)

	if(H)
		add_subdirectory(hgemm)
	endif(H)

else(CUDAToolkit_FOUND)
    message("CUDA is not installed on this system.")

endif()

if(C)
    add_subdirectory(cgemm)
endif(C)
