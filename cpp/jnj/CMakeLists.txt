cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(jj_email_srv
    VERSION 0.0.1
    DESCRIPTION "j&j assesment"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#set(CMAKE_CXX_CLANG_TIDY clang-tidy)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(inc)
include_directories(3rd-party/inc)

# add library
add_library(jj_email_srv "")
file(GLOB_RECURSE SRC_FILES src/*.cpp)
target_sources(jj_email_srv
    PRIVATE
        ${SRC_FILES}
    )
set_target_properties(jj_email_srv PROPERTIES CXX_CLANG_TIDY clang-tidy)

# add example of use
add_executable(jj_email_srv_example example/main.cpp)
target_link_libraries(jj_email_srv_example
    PRIVATE
        pthread
        jj_email_srv
    )
set_target_properties(jj_email_srv_example PROPERTIES CXX_CLANG_TIDY clang-tidy)

# add tests
option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if (ENABLE_UNIT_TESTS)
    enable_testing()

    file(GLOB TEST_FILES tests/*_test.cpp)

    add_executable(jj_email_srv_test "")
    target_sources(jj_email_srv_test 
        PRIVATE
            ${TEST_FILES}
        )

    target_link_libraries(jj_email_srv_test
        PRIVATE
            gtest_main
            gtest
            gmock
            pthread
            jj_email_srv 
        )

    include(GoogleTest)

    gtest_discover_tests(jj_email_srv_test)

endif()
