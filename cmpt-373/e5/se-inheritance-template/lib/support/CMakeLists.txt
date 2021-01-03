add_library(support)
target_sources(support
  PRIVATE
    T1Interpreter.cpp
)

target_include_directories(support
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(support PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
  PREFIX ""
)
