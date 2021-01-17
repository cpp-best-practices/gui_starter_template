#include <catch2/catch.hpp>

constexpr unsigned int Factorial(unsigned int number)
{
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed with constexpr", "[factorial]")
{
  STATIC_REQUIRE(Factorial(1) == 1);
  STATIC_REQUIRE(Factorial(2) == 2);
  STATIC_REQUIRE(Factorial(3) == 6);
  STATIC_REQUIRE(Factorial(10) == 3628800);
}
