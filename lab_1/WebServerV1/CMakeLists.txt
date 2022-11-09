cmake_minimum_required(VERSION 3.23)
project(WebServerV1)

set(CMAKE_CXX_STANDARD 14)
find_package (Threads)

#target_link_libraries (WebServerV1/lib ${CMAKE_THREAD_LIBS_INIT})
SET(CMAKE_CXX_FLAGS -pthread)

add_definitions(-DENABLE_DEBUG -DABC)

include_directories(./include/webserverv1)

#enable_testing()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

aux_source_directory(./src SRC_LIST)
add_executable(WebServerV1
        ${SRC_LIST}
#        include/webserverv1/config.h
#        include/webserverv1/request.h
#        include/webserverv1/response.h
#        include/webserverv1/url_parser.h
#        include/webserverv1/thread_encapsulation.h
#        include/webserverv1/server.h
        )

