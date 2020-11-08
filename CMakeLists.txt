add_contract(ogx.switch ogx.switch ${CMAKE_CURRENT_SOURCE_DIR}/src/ogx.switch.cpp)

target_include_directories(ogx.switch
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.system/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.token/include)


set_target_properties(ogx.switch
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/ogx.switch.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/ogx.switch.contracts.md @ONLY )

target_compile_options( ogx.switch PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
