add_library(common STATIC
  assert.h
  common_funcs.h
  common_types.h
  dynamic_bitset.cpp
  dynamic_bitset.h
  proof_chain_node.cpp
  proof_chain_node.h
)

target_compile_options(common PRIVATE ${PROMETRY_CXX_FLAGS})
