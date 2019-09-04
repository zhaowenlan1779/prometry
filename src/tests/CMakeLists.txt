add_executable(tests
    algebra/algebra_lib.cpp
    algebra/check_equation.cpp
    algebra/solve_1.cpp
    algebra/solve_2.cpp
    algebra/util_check_sign.cpp
    algebra/util_simplify_equation.cpp
    construction/line_connect.cpp
    core/element_common_parent.cpp
    core/element_intersection.cpp
    integrated/proof_output.cpp
    transform/line_parallel_transitivity.cpp
    transform/line_segment_concat.cpp
    tests.cpp
)

target_link_libraries(tests PRIVATE common core geometry algebra)
target_link_libraries(tests PRIVATE catch-single-include)

add_test(NAME tests COMMAND tests)
