set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

enable_testing()

add_test_exec(dp_ch01)
add_test_exec(dp_ch02)
add_test_exec(dp_ch04)
add_test_exec(dp_ch05)
add_test_exec(dp_ch06)
add_test_exec(dp_ch07)
add_test_exec(dp_ch08)

set_tests_properties(
    dp_ch01
    dp_ch02
    dp_ch04
    dp_ch05
    dp_ch06
    dp_ch07
    dp_ch08
    PROPERTIES
        LABELS dp
    )

