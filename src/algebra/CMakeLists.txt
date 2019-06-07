add_library(algebra STATIC
    algebra.cpp
    algebra.h
)

target_link_libraries(algebra PRIVATE common symengine)
target_compile_options(algebra PRIVATE ${PROMETRY_CXX_FLAGS})
