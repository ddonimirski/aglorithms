set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

enable_testing()

add_test_exec(backpropagation)

set_tests_properties(
    backpropagation
    PROPERTIES
        LABELS
        backpropagation
    )
