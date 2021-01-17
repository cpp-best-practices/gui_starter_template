#include "HelloQt.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

HelloQt::HelloQt(QWidget *parent) : QWidget(parent)
{
  // The memory management is not done explicitly but by using the parent
  // relationship built into Qt
  // The tr calls are not strictly neccesary, but it is all that is needed for
  // future i18n.
  auto mainLayout = new QVBoxLayout;
  auto descriptiveLabel = new QLabel(tr("Descriptive"));
  auto pushButton = new QPushButton(tr("Push me!"));
  auto grouping = new QHBoxLayout;
  auto directButton = new QPushButton(tr("Directly!"));
  auto fatal = new QPushButton(tr("Don't push this button"));
  // By adding the widgets to the main widget, they get parented and the
  // parenting takes care of freeing the memory.
  // Laying out in layouts makes the GUI automatically resize.
  grouping->addWidget(descriptiveLabel);
  grouping->addWidget(pushButton);
  mainLayout->addLayout(grouping);
  mainLayout->addWidget(directButton);
  mainLayout->addWidget(fatal);
  setLayout(mainLayout);
  // Signals and slots are use to simply define relationships between actions
  // and effects
  // By using this "new style" connect the types are checked at compile time to
  // match
  connect(pushButton, &QPushButton::clicked, this, &HelloQt::writeToDebug);
  // Lambdas can also be used as can ordinary freestanding functions
  connect(directButton, &QPushButton::clicked, []() { qDebug() << tr("I am in line"); });
  // Most usefull signals and slots are already built into the framework.
  connect(fatal, &QPushButton::clicked, this, &HelloQt::close);// could just use close
};

void HelloQt::writeToDebug(void)
{
  qDebug() << tr("I don't know what I was supposed to debug here...");
}
