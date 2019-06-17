#include <catch2/catch.hpp>

//         Test Description,          Command Line Argument
TEST_CASE( "The identity property is satisfied on addition", "[additive-identity]" ) {
  REQUIRE( 1 + 0 == 1 );
}