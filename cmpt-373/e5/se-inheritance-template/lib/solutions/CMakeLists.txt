add_library(solutions)
target_sources(solutions
  PRIVATE
    task01.cpp
    task02.cpp
    #task03.cpp
)

target_include_directories(solutions
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(solutions
  PUBLIC
    support
)

set_target_properties(solutions PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
  PREFIX ""
)

