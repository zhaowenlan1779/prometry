add_library(geometry STATIC
    conclusion/line_parallel.cpp
    conclusion/line_parallel.h
    element/line.cpp
    element/line.h
    element/point.cpp
    element/point.h
    element/standalone_line.cpp
    element/standalone_line.h
    transform/line_parallel_transitivity.cpp
    transform/line_parallel_transitivity.h
)

target_link_libraries(geometry PUBLIC common PRIVATE core)
target_compile_options(geometry PRIVATE ${PROMETRY_CXX_FLAGS})
