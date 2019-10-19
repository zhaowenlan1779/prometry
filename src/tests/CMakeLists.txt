add_executable(tests
    algebra/algebra_lib.cpp
    algebra/check_equation.cpp
    algebra/util_check_sign.cpp
    algebra/util_equation_to_string.cpp
    algebra/util_simplify_equation.cpp
    common/dynamic_bitset.cpp
    common/string_pack.cpp
    construction/line_connect.cpp
    construction/triangle_make.cpp
    core/element_common_parent.cpp
    core/element_intersection.cpp
    element/triangle_order.cpp
    integrated/proof_output.cpp
    integrated/pythagorean.cpp
    integrated/triangle_equality_1.cpp
    integrated/triangle_equality_2.cpp
    transform/algebra/line_segment_concat.cpp
    transform/parallel/angles_to_parallel.cpp
    transform/parallel/angles_to_prependicular.cpp
    transform/parallel/line_parallel_transitivity.cpp
    transform/parallel/parallel_to_angles.cpp
    transform/parallel/prependicular_to_angles.cpp
    transform/pythagorean/pythagorean.cpp
    transform/triangle/aa_similar.cpp
    transform/triangle/aas_asa.cpp
    transform/triangle/angles_to_isosceles.cpp
    transform/triangle/hl_similar.cpp
    transform/triangle/isosceles_to_angles.cpp
    transform/triangle/sas_similar.cpp
    transform/triangle/similar_to_angles.cpp
    transform/triangle/similar_to_line_segment_ratio.cpp
    transform/triangle/sss_similar.cpp
    transform/triangle/triangle_internal_angles.cpp
    tests.cpp
)

target_link_libraries(tests PRIVATE common core geometry algebra)
target_link_libraries(tests PRIVATE catch-single-include)

add_test(NAME tests COMMAND tests)
