#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  sf::Texture texture;
  sf::Sprite sprite;
  texture.create(320, 200);
  sprite.setTexture(texture);
  sprite.setScale(2.0, 2.0);

  std::vector<std::uint8_t> screen_ram(320 * 200 * 4, 0);
  for (std::uint8_t value; auto &pixel : screen_ram) { pixel = (value += 13); }
  texture.update(screen_ram.data());

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) { window.close(); }
    }

    ImGui::SFML::Update(window, deltaClock.restart());

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();

    ImGui::Begin("VICII", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      ImGui::Image(sprite);
    }
    ImGui::End();

    window.clear();
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
