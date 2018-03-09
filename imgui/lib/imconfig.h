#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#define IM_VEC2_CLASS_EXTRA                                             \
    template <typename T>                                               \
    ImVec2(const sf::Vector2<T>& v) {                                   \
        x = static_cast<float>(v.x);                                    \
        y = static_cast<float>(v.y);                                    \
    }                                                                   \
                                                                        \
    template <typename T>                                               \
    operator sf::Vector2<T>() const {                                   \
        return sf::Vector2<T>(x, y);                                    \
    }

#define IM_VEC4_CLASS_EXTRA                                             \
    ImVec4(const sf::Color & c)                                         \
        : ImVec4(c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f) {  \
    }                                                                   \
    operator sf::Color() const {                                        \
        return sf::Color(static_cast<sf::Uint8>(x * 255.f),             \
            static_cast<sf::Uint8>(y * 255.f),                          \
            static_cast<sf::Uint8>(z * 255.f),                          \
            static_cast<sf::Uint8>(w * 255.f));                         \
    }