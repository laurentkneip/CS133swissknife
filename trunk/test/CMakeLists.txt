add_executable( test_logger test_logger.cpp )
target_link_libraries( test_logger swissknife )

add_executable( test_lap_timer test_lap_timer.cpp )
target_link_libraries( test_lap_timer swissknife )

add_executable( test_valgrind test_valgrind.cpp )

add_executable( test_gdb test_gdb.cpp )