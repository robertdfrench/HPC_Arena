#pragma once

#include <SFML/Graphics.hpp>

// Struct containing all the information required to render a sprite
struct SpriteRenderable {
  const sf::Texture& texture;
  sf::FloatRect rectangle;
  SpriteRenderable(const sf::Texture& texture, const sf::FloatRect& rectangle):
                   texture{texture}, rectangle{rectangle} {}
};
