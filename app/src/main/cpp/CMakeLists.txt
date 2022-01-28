# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("iva")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -static-openmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -static-openmp")

set(DEBUG_UTILS_PATH "debug-utils")
set(DEBUG_UTILS_SOURCES ${DEBUG_UTILS_PATH}/trace.cpp)

set(ENGINE_PATH "engine")
set(ENGINE_SOURCES ${ENGINE_PATH}/AudioInputEngine.cpp
                   ${ENGINE_PATH}/AudioOutputEngine.cpp
                   ${ENGINE_PATH}/AudioIOEngine.cpp
                   ${ENGINE_PATH}/IVAProcessor.cpp)

set(BUFFERING_PATH "buffering")
set(BUFFERING_SOURCES ${BUFFERING_PATH}/RingBuffer.cpp
                      ${BUFFERING_PATH}/AsyncRingBuffer.cpp)

set(MATLAB_PATH "MATLAB")
set(MATLAB_SOURCES ${MATLAB_PATH}/compute_iva.cpp
                   ${MATLAB_PATH}/compute_iva_data.cpp
                   ${MATLAB_PATH}/compute_iva_initialize.cpp
                   ${MATLAB_PATH}/compute_iva_rtwutil.cpp
                   ${MATLAB_PATH}/compute_iva_terminate.cpp
                   ${MATLAB_PATH}/fft.cpp
                   ${MATLAB_PATH}/flip.cpp
                   ${MATLAB_PATH}/ifft.cpp
                   ${MATLAB_PATH}/init_iva.cpp
                   ${MATLAB_PATH}/pinv.cpp
                   ${MATLAB_PATH}/rt_nonfinite.cpp
                   ${MATLAB_PATH}/rtGetInf.cpp
                   ${MATLAB_PATH}/rtGetNaN.cpp
                   ${MATLAB_PATH}/svd.cpp
                   ${MATLAB_PATH}/xdotc.cpp
                   ${MATLAB_PATH}/xnrm2.cpp
                   ${MATLAB_PATH}/xrot.cpp
                   ${MATLAB_PATH}/xrotg.cpp
                   ${MATLAB_PATH}/xswap.cpp
        )

include_directories(Eigen)

# Build our own native library
add_library (native-lib SHARED
             native-lib.cpp
             ${DEBUG_UTILS_SOURCES}
             ${BUFFERING_SOURCES}
             ${ENGINE_SOURCES}
             ${MATLAB_SOURCES})

target_include_directories(native-lib PRIVATE
                           ${DEBUG_UTILS_PATH}
                           ${BUFFERING_PATH}
                           ${ENGINE_PATH}
                           ${MATLAB_PATH})

# Find the Oboe package
find_package (oboe REQUIRED CONFIG)
#find_package(OpenMP REQUIRED)

# Specify the libraries which our native library is dependent on, including Oboe
target_link_libraries(native-lib android log atomic oboe::oboe -static-openmp -fopenmp)