#include <functional>
#include <iostream>

int main()
{
  [out = std::ref(std::cout << "Hello ")]() { out.get() << "World\n"; }
  ();
}
