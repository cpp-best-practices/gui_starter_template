#include "MainWindow.h"
#include <QBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent) :
  QWidget(parent)
{
  // Create a button and hook up click event to close main window
  auto button = new QPushButton("Click to close");
  connect(
    button, &QPushButton::clicked,
    [this] {
      close();
    }
  );

  // Add button to this widget's layout
  auto layout = new QVBoxLayout;
  layout->addWidget(button);
  setLayout(layout);
}
