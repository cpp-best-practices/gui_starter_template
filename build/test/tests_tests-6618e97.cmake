add_test( [==[unittests.Factorials are computed]==] /workspace/template-cpp/build/bin/tests [==[Factorials are computed]==] [==[--reporter xml]==] [==[--out /workspace/template-cpp/build/test/./unittests.Factorials_are_computed.xml]==])
set_tests_properties( [==[unittests.Factorials are computed]==] PROPERTIES WORKING_DIRECTORY /workspace/template-cpp/build/test)
set( tests_TESTS [==[unittests.Factorials are computed]==])
