cmake_minimum_required(VERSION 3.23)
project(StopWait)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPTLER GCC)
set(CMAKE_CXX FLAGS -fexec-charset=GBK)

add_definitions(-std=c++14)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/StopWait)
include_directories(${PROJECT_SOURCE_DIR}/include/GBN)
include_directories(${PROJECT_SOURCE_DIR}/include/SR)
include_directories(${PROJECT_SOURCE_DIR}/include/TCP)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/ SRC_LIST)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(RDTP_LAB ${SRC_LIST})
find_library(NETSIM_LIB libnetsim.a ${PROJECT_SOURCE_DIR}/lib)
TARGET_LINK_LIBRARIES(RDTP_LAB ${NETSIM_LIB})
