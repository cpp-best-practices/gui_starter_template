#include <iterator>
#include <utility>
#include <fmt/format.h>

[[nodiscard]] auto sum_values(const uint8_t *Data, size_t Size)
{
  int value = 0;
  for (std::size_t offset = 0; offset < Size; ++offset) {
    value += static_cast<unsigned int>(*(Data + offset)) * 1000;
  }
  return value;
}

// Fuzzer that attempts to invoke undefined behavior for signed integer overflow
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
  fmt::print("Value sum: {}, len{}\n", sum_values(Data,Size), Size);
  return 0;
}
