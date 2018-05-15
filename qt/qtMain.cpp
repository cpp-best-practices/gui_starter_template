#include "HelloQt.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  HelloQt dialog;
  dialog.show();

  return app.exec();// this runs the main event loop and sees to it that cleanup is done
}
