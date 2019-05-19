add_executable(tests
    transform/line_parallel_transitivity.cpp
    tests.cpp
)

target_link_libraries(tests PRIVATE common core geometry)
target_link_libraries(tests PRIVATE catch-single-include)

add_test(NAME tests COMMAND tests)
