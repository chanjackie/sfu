add_library(sortIntegers SortIntegers.cpp)

set_target_properties(sortIntegers PROPERTIES PUBLIC_HEADER include/SortIntegers.h)

target_include_directories(sortIntegers	
	PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
	$<INSTALL_INTERFACE:include>)

install(TARGETS sortIntegers
	PUBLIC_HEADER
		DESTINATION include)