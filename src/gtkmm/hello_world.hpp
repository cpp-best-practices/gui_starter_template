#ifndef GTKMM_EXAMPLE_HELLO_WORLD_HPP
#define GTKMM_EXAMPLE_HELLO_WORLD_HPP

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class HelloWorld : public Gtk::Window
{

public:
  HelloWorld();

protected:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Button m_button;
};

#endif// GTKMM_EXAMPLE_HELLO_WORLD_HPP
