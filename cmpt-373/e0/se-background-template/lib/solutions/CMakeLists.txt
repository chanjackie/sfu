add_library(solutions)
target_sources(solutions
  PRIVATE
    task01.cpp
    task02.cpp
    task03.cpp
    task04.cpp
    task05.cpp
    task06.cpp
    task07.cpp
    task08.cpp
)

target_include_directories(solutions
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(solutions
  PUBLIC
    support
)