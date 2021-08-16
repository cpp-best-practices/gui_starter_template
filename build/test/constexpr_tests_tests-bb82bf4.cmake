add_test( [==[constexpr.Factorials are computed with constexpr]==] /workspace/template-cpp/build/bin/constexpr_tests [==[Factorials are computed with constexpr]==] [==[--reporter xml]==] [==[--out /workspace/template-cpp/build/test/./constexpr.Factorials_are_computed_with_constexpr.xml]==])
set_tests_properties( [==[constexpr.Factorials are computed with constexpr]==] PROPERTIES WORKING_DIRECTORY /workspace/template-cpp/build/test)
set( constexpr_tests_TESTS [==[constexpr.Factorials are computed with constexpr]==])
