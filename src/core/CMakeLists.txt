add_library(core STATIC
    conclusion.cpp
    conclusion.h
    element.cpp
    element.h
    printer.h
    system.cpp
    system.h
    transform.h
)

target_link_libraries(core PRIVATE common algebra)
target_compile_options(core PRIVATE ${PROMETRY_CXX_FLAGS})
