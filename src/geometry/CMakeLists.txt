add_library(geometry STATIC
    conclusion/conclusion_types.h
    conclusion/line_parallel.cpp
    conclusion/line_parallel.h
    conclusion/line_prependicular.cpp
    conclusion/line_prependicular.h
    construction/line_connect.cpp
    construction/line_connect.h
    construction/all_constructions.h
    element/element_types.h
    element/line.cpp
    element/line.h
    element/line_angle.cpp
    element/line_angle.h
    element/line_segment.cpp
    element/line_segment.h
    element/point.cpp
    element/point.h
    transform/algebra/line_segment_concat.cpp
    transform/algebra/line_segment_concat.h
    transform/all_transforms.h
    transform/line_parallel_transitivity.cpp
    transform/line_parallel_transitivity.h
    transform/parallel_to_angles.cpp
    transform/parallel_to_angles.h
    transform/pythagorean.cpp
    transform/pythagorean.h
)

target_link_libraries(geometry PRIVATE common core)
target_compile_options(geometry PRIVATE ${PROMETRY_CXX_FLAGS})
