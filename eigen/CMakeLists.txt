cmake_minimum_required(VERSION 3.1)
project(eigen)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-w)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3") # !!!!!
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funroll-loops")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -msse -msse2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -mfma") # !!!!!
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEIGEN_FAST_MATH -DEIGEN_NO_DEBUG")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -S")

if(DEFINED ENV{ARM_ARCHITECTURE})
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -mfpu=neon -march=armv7-a")
else()
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -msse -msse4.2 -msse2")
endif()

find_package(OpenMP) # !!!!!
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# set(Eigen3_DIR "/opt/eigen-337/share/eigen3/cmake/")
find_package(Eigen3 REQUIRED)
if(Eigen3_FOUND)
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()

# find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
# if(OpenCV_FOUND)
#     include_directories(${OpenCV_INCLUDE_DIRS})
#     link_libraries(${OpenCV_LIBS})
# endif()

add_executable(eigen_matrix eigen_matrix.cpp)

add_executable(eigen_simd_test eigen_simd_test.cpp)

add_executable(eigen_matrix_mul eigen_matrix_mul.cpp)
# target_compile_options(eigen_simd_test PUBLIC "-S")

