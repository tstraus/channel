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
    "tests.cpp"
)

add_executable(${PROJECT_NAME}
    ${SOURCE}
    ${HEADER}
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
    gtest
    gtest_main
)