
add_library(doctest-main OBJECT
  "doctest.cpp"
)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


function(can_compile_unit unit_path)
  try_compile(
    CAN_COMPILE
    ${CMAKE_CURRENT_BINARY_DIR}/trials
    ${unit_path}
    CMAKE_FLAGS
      "-DINCLUDE_DIRECTORIES=${CMAKE_CURRENT_SOURCE_DIR}"
  ) 
  set(CAN_COMPILE ${CAN_COMPILE} PARENT_SCOPE)
endfunction(can_compile_unit)


function(compile_unit_test unit_name unit_path)
  add_executable(${unit_name})
  target_sources(${unit_name}
    PRIVATE
      ${unit_path}
  )
  target_link_libraries(${unit_name}
    doctest-main
    solutions
    support
  )
  set_target_properties(${unit_name} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 20
    PREFIX ""
  )

  add_test(NAME ${unit_name}
    COMMAND ${unit_name}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )
endfunction(compile_unit_test)


function(add_simple_system_target name policy)
  set(TEST_ID "system--${policy}--${name}")
  set(OUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_ID}")
  add_custom_command(OUTPUT ${OUT_PATH}
    COMMAND "$<TARGET_FILE:tolerator>" --${policy} ${CMAKE_CURRENT_SOURCE_DIR}/ll/${name}.ll -o ${OUT_PATH}
    DEPENDS tolerator ${name}_ll
    BYPRODUCTS ${OUT_PATH}
    COMMENT "Instrumenting test for ${OUT_PATH}"
    VERBATIM
  )
  add_custom_target(${TEST_ID}_test DEPENDS ${OUT_PATH})
  set_property(TARGET ${TEST_ID}_test PROPERTY EXCLUDE_FROM_ALL OFF)
endfunction(add_simple_system_target)



function(add_system_test system_target policy increase_count)
  set(TEST_PROGRAM "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/system--${policy}--${system_target}")
  set(TEST_ID "system--${SYSTEM_TEST_COUNT}--${policy}--${system_target}")
  add_test(NAME "${TEST_ID}"
    COMMAND ${TEST_PROGRAM} ${ARGN}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )
  set_tests_properties("${TEST_ID}" PROPERTIES LABELS "${testcase} ${policy}")

  if (increase_count)
    math(EXPR SYSTEM_TEST_COUNT "${SYSTEM_TEST_COUNT}+1")
  endif()
  set(SYSTEM_TEST_COUNT ${SYSTEM_TEST_COUNT} PARENT_SCOPE)
endfunction(add_system_test)


function(simple_all_policies_unit_test unit_name)
  add_simple_unit_test(${unit_name} log)
  add_simple_unit_test(${unit_name} ignore)
  add_simple_unit_test(${unit_name} defaults)
  add_simple_unit_test(${unit_name} returns)
endfunction(simple_all_policies_unit_test)


function(simple_all_policies_system_target name)
  add_simple_system_target(${name} log)
  add_simple_system_target(${name} ignore)
  add_simple_system_target(${name} defaults)
  add_simple_system_target(${name} returns)
endfunction(simple_all_policies_system_target)


function(simple_all_policies_system_test name)
  add_system_test(${name} log NO ${ARGN})
  add_system_test(${name} ignore NO ${ARGN})
  add_system_test(${name} defaults NO ${ARGN})
  add_system_test(${name} returns YES ${ARGN})
  set(SYSTEM_TEST_COUNT ${SYSTEM_TEST_COUNT} PARENT_SCOPE)
endfunction(simple_all_policies_system_test)

compile_unit_test(unit01 unit01.cpp)
compile_unit_test(unit02 unit02.cpp)
compile_unit_test(unit03 unit03.cpp)
compile_unit_test(unit04 unit04.cpp)
compile_unit_test(unit05 unit05.cpp)
compile_unit_test(unit06 unit06.cpp)
