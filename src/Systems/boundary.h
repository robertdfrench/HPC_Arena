#pragma once

#include "ECS_core/system.h"
#include "ECS_core/entity_manager.h"
#include "Components/position.h"
#include "boundary.h"
#include "SFML/System/Vector2.hpp"

class Boundary: public ecs::System {
public:
  Boundary(const sf::Vector2u& size): size_{size} {};
  void update(ecs::EntityManager& entity_manager, float dt) override;

private:
  sf::Vector2u size_;
};
