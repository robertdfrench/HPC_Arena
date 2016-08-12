#pragma once

#include "ECS_core/entity_manager.h"
#include "ECS_core/system_manager.h"
#include <SFML/Window.hpp>

class GameManager {
public:
  GameManager(): window_{sf::VideoMode(800, 600), "Arena"} {};

  template<typename EntityType>
  ecs::Entity& add_entity() {
    return entity_manager_.create<EntityType>();
  }

  template<typename SystemType>
  void enable_system() {
    system_manager_.enable<SystemType>();
  }

  void update_systems(float dt) {
    system_manager_.update(entity_manager_, dt);
  }

private:
  ecs::EntityManager entity_manager_;
  ecs::SystemManager system_manager_;
  sf::Window window_;
};
