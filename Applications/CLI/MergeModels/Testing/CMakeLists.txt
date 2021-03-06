
#-----------------------------------------------------------------------------
# MergeModels tests
#-----------------------------------------------------------------------------
set(BASELINE ${CMAKE_CURRENT_SOURCE_DIR}/../Data/Baseline)
set(CLP MergeModels)

add_executable(${CLP}Test ${CLP}Test.cxx)
add_dependencies(${CLP}Test ${CLP})
target_link_libraries(${CLP}Test ${CLP}Lib ${ITK_LIBRARIES})
set_target_properties(${CLP}Test PROPERTIES LABELS ${CLP})

set(testname ${CLP}Test)
add_test(NAME ${testname} COMMAND ${Launcher_Command} $<TARGET_FILE:${CLP}Test>
  ModuleEntryPoint
    ${MRML_TEST_DATA}/sphere.vtk
    ${MRML_TEST_DATA}/cube.vtk
    ${TEMP}/sphereCube.vtk
  )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})

set(testname ${CLP}TestVtp)
add_test(NAME ${testname} COMMAND ${Launcher_Command} $<TARGET_FILE:${CLP}Test>
  ModuleEntryPoint
    ${MRML_TEST_DATA}/sphere.vtp
    ${MRML_TEST_DATA}/cube.vtp
    ${TEMP}/sphereCube.vtp
  )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})

# add a test that compares the outline to a baseline .vtp
set(testname ${CLP}TestCompare)
add_test(NAME ${testname} COMMAND ${Launcher_Command} ${CMAKE_COMMAND}
  -Dtest_cmd=$<TARGET_FILE:${CLP}Test>
  -Dtest_name=ModuleEntryPoint
  -Dmodel1=${MRML_TEST_DATA}/sphere.vtp
  -Dmodel2=${MRML_TEST_DATA}/cube.vtp
  -Doutput_model=${TEMP}/sphereCube.vtp
  -Doutput_baseline=${BASELINE}/sphereCube.vtp
  -Doutput_test=${TEMP}/sphereCube.vtp
  -P ${CMAKE_CURRENT_SOURCE_DIR}/run_MergeModelsTest.cmake
  )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})

