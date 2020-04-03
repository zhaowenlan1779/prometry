add_library(common STATIC
  assert.h
  common_types.h
  dynamic_bitset.cpp
  dynamic_bitset.h
  printer.cpp
  printer.h
  proof_chain_node.cpp
  proof_chain_node.h
)
create_target_directory_groups(common)

target_compile_options(common PRIVATE ${PROMETRY_CXX_FLAGS})
