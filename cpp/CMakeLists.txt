# minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_COMPILER clang++)

# project name and language
project(algorithms LANGUAGES CXX)


# required c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(GNUInstallDirs)

#include_directories(utils)
include_directories(.)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})



option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")


macro(add_test_exec _name)

    add_executable(test_${_name} "")

    target_sources(test_${_name}
        PRIVATE
        test_${_name}.cpp
        )

    target_link_libraries(test_${_name}
        PRIVATE
        gtest_main
        )


    add_test(
        NAME ${_name}
        COMMAND $<TARGET_FILE:test_${_name}>
        )
endmacro()


if(ENABLE_UNIT_TESTS)

    include(CTest)

    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.8.0
        )

    FetchContent_GetProperties(googletest)

    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)

        # Prevent GoogleTest from overriding our compiler/linker
        # options
        # when building with Visual Studio
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        # Prevent GoogleTest from using PThreads
        set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

        # adds the targers: gtest, gtest_main, gmock,
        # gmock_main
        add_subdirectory(
            ${googletest_SOURCE_DIR}
            ${googletest_BINARY_DIR}
            )

        # Silence std::tr1 warning on MSVC
        if(MSVC)
            foreach(_tgt gtest gtest_main gmock gmock_main)
                target_compile_definitions(${_tgt}
                    PRIVATE
                    "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
                    )
            endforeach()
        endif()
    endif()

    #dir to tests
    add_subdirectory(utils)
    add_subdirectory(150_cci)
    add_subdirectory(crack_interview_6th)
    add_subdirectory(dp)

endif()
