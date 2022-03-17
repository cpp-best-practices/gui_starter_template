#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <iostream>

int main()
{
  // very important notes:
  // the undeleted window and undeleted box don't actually cause memory leaks
  //
  // HOWEVER: the application still generates a few memory leak on shutdown
  // because FontConfig stuff is not properly cleaned up. It is not
  // clear if it is possible to fix this in the context of a trivial
  // FLTK application, or if ASAN suppressions should be added
  // https://clang.llvm.org/docs/AddressSanitizer.html#suppressing-reports-in-external-libraries

  Fl_Window *window = new Fl_Window(640, 480, "Hello, World!");
  [[maybe_unused]] Fl_Box *box = new Fl_Box(20, 40, 300, 100, "A box!");
  window->end();
  window->show();
  const auto retval = Fl::run();
  return retval;
}
