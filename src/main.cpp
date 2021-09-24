//
// The full include-list reported from include-what-you-use
//
#include <docopt/docopt.h>  // for docopt
#include <docopt/docopt_value.h>   // for operator<<, value
#include <fmt/format.h>     // for make_format_args, print, vformat_to
#include <spdlog/spdlog.h>  // for info
#include <exception>        // for exception
#include <iostream>         // for string, char_traits, operator<<, basic_os...
#include <iterator>         // for next
#include <map>              // for map, __map_iterator, operator!=
#include <type_traits>      // for enable_if<>::type
#include <utility>          // for pair

static constexpr auto USAGE =
  R"(Naval Fate.

    Usage:
          naval_fate ship new <name>...
          naval_fate ship <name> move <x> <y> [--speed=<kn>]
          naval_fate ship shoot <x> <y>
          naval_fate mine (set|remove) <x> <y> [--moored | --drifting]
          naval_fate (-h | --help)
          naval_fate --version
    Options:
          -h --help     Show this screen.
          --version     Show version.
          --speed=<kn>  Speed in knots [default: 10].
          --moored      Moored (anchored) mine.
          --drifting    Drifting mine.
)";

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
  std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
    { std::next(argv), std::next(argv, argc) },
    true,// show help if requested
    "Naval Fate 2.0");// version string

  for (auto const &arg : args) {
    std::cout << arg.first << "=" << arg.second << std::endl;
  }


  //Use the default logger (stdout, multi-threaded, colored)
  spdlog::info("Hello, {}!", "World");

  fmt::print("Hello, from {}\n", "{fmt}");
}
