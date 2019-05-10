add_executable( test_logger test_logger.cpp )
target_link_libraries( test_logger swissknife )

add_executable( test_lap_timer test_lap_timer.cpp )
target_link_libraries( test_lap_timer swissknife )

add_executable( test_valgrind test_valgrind.cpp )

add_executable( test_gdb test_gdb.cpp )

add_executable( test_hammingDistance1 test_hammingDistance1.cpp )
target_link_libraries( test_hammingDistance1 swissknife )

add_executable( test_hammingDistance2 test_hammingDistance2.cpp )
target_link_libraries( test_hammingDistance2 swissknife )

#Run unit tests
add_test( unittest_logger test_logger )
add_test( unittest_lap_timer test_lap_timer )
add_test( unittest_valgrind test_valgrind )
add_test( unittest_gdb test_gdb )