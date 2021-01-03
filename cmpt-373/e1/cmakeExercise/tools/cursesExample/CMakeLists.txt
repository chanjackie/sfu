add_executable(cursesExample main.cpp)
set_target_properties(cursesExample PROPERTIES CXX_STANDARD 17)

set(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)

target_link_libraries(cursesExample ${CURSES_LIBRARIES})

install(TARGETS cursesExample
	RUNTIME DESTINATION bin)