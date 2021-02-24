#include <iterator>
#include <utility>
#include <fmt/format.h>

[[nodiscard]] auto sum_values(const uint8_t *Data, size_t Size)
{
  constexpr auto scale = 1000;

  int value = 0;
  for (std::size_t offset = 0; offset < Size; ++offset) {
    value += static_cast<int>(*std::next(Data, static_cast<long>(offset))) * scale;
  }
  return value;
}

// Fuzzer that attempts to invoke undefined behavior for signed integer overflow
// cppcheck-suppress unusedFunction symbolName=LLVMFuzzerTestOneInput
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
  constexpr auto side_effect = 1;
  static_assert([] {
    int i = 0;
    assert(i++ == 0);   // NOLINT
    return i;
  }() == side_effect, "Assertions are disabled but are required for fuzz testing");

  const auto sum = sum_values(Data, Size);
  fmt::print("Value sum: {}, len{}\n", sum, Size);
  assert(sum >= 0); // NOLINT
  
  return 0;
}
