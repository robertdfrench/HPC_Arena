#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "ECS_core/system.h"
#include "ECS_core/entity_manager.h"
#include "Rendering/texture_cache.h"
#include "Components/position.h"
#include "Components/sprite.h"

class Renderer: public ecs::System {
public:
  Renderer(sf::RenderWindow& window);
  void update(ecs::EntityManager& entity_manager, float dt) override;
private:
  sf::RenderWindow& window_;
  TextureCache texture_cache_;
};
