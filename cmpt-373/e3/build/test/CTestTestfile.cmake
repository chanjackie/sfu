# CMake generated Testfile for 
# Source directory: /mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test
# Build directory: /mnt/c/sfu-cmpt/cmpt-373/e3/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(AllTests "/mnt/c/sfu-cmpt/cmpt-373/e3/build/test/runAllTests")
set_tests_properties(AllTests PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/CMakeLists.txt;17;add_test;/mnt/c/sfu-cmpt/cmpt-373/e3/exercise-unit-tests/test/CMakeLists.txt;0;")
subdirs("gtest")
