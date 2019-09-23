add_executable(tests
    algebra/algebra_lib.cpp
    algebra/check_equation.cpp
    algebra/solve_1.cpp
    algebra/solve_2.cpp
    algebra/util_check_sign.cpp
    algebra/util_equation_to_string.cpp
    algebra/util_simplify_equation.cpp
    common/dynamic_bitset.cpp
    construction/line_connect.cpp
    construction/triangle_make.cpp
    core/element_common_parent.cpp
    core/element_intersection.cpp
    integrated/proof_output.cpp
    integrated/pythagorean.cpp
    transform/algebra/line_segment_concat.cpp
    transform/parallel/angles_to_parallel.cpp
    transform/parallel/angles_to_prependicular.cpp
    transform/parallel/line_parallel_transitivity.cpp
    transform/parallel/parallel_to_angles.cpp
    transform/parallel/prependicular_to_angles.cpp
    transform/pythagorean/pythagorean.cpp
    transform/triangle/triangle_internal_angles.cpp
    tests.cpp
)

target_link_libraries(tests PRIVATE common core geometry algebra)
target_link_libraries(tests PRIVATE catch-single-include)

add_test(NAME tests COMMAND tests)
