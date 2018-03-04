cmake_minimum_required(VERSION 3.0)
project(ChannelTest)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

include_directories(".")

set(SOURCE "test.cpp")

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
