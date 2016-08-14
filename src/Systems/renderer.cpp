#include "Components/position.h"
#include "Components/sprite.h"
#include "ECS_core/entity_manager.h"
#include "renderer.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

Renderer::Renderer(sf::RenderWindow& window) : window_{window} {}

void Renderer::update(ecs::EntityManager& entity_manager, float dt) {
  window_.clear();

  entity_manager.for_each<Position, Sprite>([this, dt] (Position& position, Sprite& sprite) {
    sf::Sprite nsprite;
    nsprite.setTexture(texture_cache_.get(sprite.filename));
    nsprite.setPosition(sf::Vector2f(position.x, position.y));
    window_.draw(nsprite);
  });

  window_.display();

};
