cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(jj_email_srv
    VERSION 0.0.1
    DESCRIPTION "j&j assesment"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_CXX_CLANG_TIDY clang-tidy)


include_directories(inc)

add_library(jj_email_srv_default "")

file(GLOB_RECURSE SRC_FILES src/*.cpp)

target_sources(jj_email_srv_default
    PRIVATE
        ${SRC_FILES}
    )

set_target_properties(jj_email_srv_default PROPERTIES CXX_CLANG_TIDY clang-tidy)

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
            pthread
            jj_email_srv_default 
        )

    include(GoogleTest)

    gtest_discover_tests(jj_email_srv_test)

endif()
