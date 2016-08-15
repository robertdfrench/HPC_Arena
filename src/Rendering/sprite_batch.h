#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "sprite_renderable.h"

class SpriteBatch: public sf::Drawable, public sf::Transformable {
public:
  SpriteBatch(const std::vector<SpriteRenderable>& sprite_renderables);

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  sf::VertexArray vertices_;
  const sf::Texture& texture_;
};
