#include "MainWindow.h"
#include <QBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent) :
  QWidget(parent)
{
  auto layout = new QVBoxLayout;
  auto button = new QPushButton("Click me");
  layout->addWidget(button);
  setLayout(layout);
}
