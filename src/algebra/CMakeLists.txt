add_library(algebra STATIC
    algebra.cpp
    algebra.h
    util.cpp
    util.h
)

# Note: linking gmp in is required somehow.
# TODO: figure out this
target_link_libraries(algebra PRIVATE common symengine gmp)
target_compile_options(algebra PRIVATE ${PROMETRY_CXX_FLAGS})
