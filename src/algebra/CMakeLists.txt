add_library(algebra STATIC
    algebra.cpp
    algebra.h
    util.cpp
    util.h
)

target_link_libraries(algebra PUBLIC common ${SYMENGINE_LIBRARIES})
target_compile_options(algebra PRIVATE ${PROMETRY_CXX_FLAGS})
