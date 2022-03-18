
// FLTK has warnings in Level 4 that we cannot work around
// so we force those headers to be included with /W3
#pragma warning(push, 3)
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#pragma warning(pop)


#include <iostream>

int main()
{
  // very important note:
  // 
  // The application generates a few memory leaks on shutdown
  // because FontConfig stuff is not properly cleaned up. It is not
  // clear if it is possible to fix this in the context of a trivial
  // FLTK application, or if ASAN suppressions should be added
  // https://clang.llvm.org/docs/AddressSanitizer.html#suppressing-reports-in-external-libraries

  auto window = std::make_unique<Fl_Window>(640, 480, "Hello, World!"); // NOLINT (magic numbers)
  auto box = std::make_unique<Fl_Box>(20, 40, 300, 100, "A box!"); // NOLINT (magic numbers)
  window->end();
  window->show();
  return Fl::run();
}
