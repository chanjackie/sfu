add_executable(fibSorter main.cpp)

target_link_libraries(fibSorter
	PUBLIC sortIntegers)

set_target_properties(fibSorter PROPERTIES CXX_STANDARD 17)

install(TARGETS fibSorter
	RUNTIME DESTINATION bin)