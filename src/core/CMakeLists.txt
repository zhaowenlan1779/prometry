add_library(core STATIC
    conclusion.cpp
    conclusion.h
    element.cpp
    element.h
    system.cpp
    system.h
    transform.h
)
create_target_directory_groups(core)

target_link_libraries(core PUBLIC common)
target_link_libraries(core PRIVATE algebra)
target_compile_options(core PRIVATE ${PROMETRY_CXX_FLAGS})
