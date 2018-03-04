project(ChannelTest)

find_package(Threads)

include_directories(
    ".."
    "../deps/gtest/googletest/include"
)

set(HEADER
    "../channel.h"
)

set(SOURCE
    "gtest.cpp"
)

add_executable(${PROJECT_NAME}
    ${SOURCE}
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
    gtest
    gtest_main
)