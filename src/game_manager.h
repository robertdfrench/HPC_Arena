#pragma once

#include <SFML/Window.hpp>
#include "ECS_core/entity_manager.h"
#include "ECS_core/system_manager.h"

class GameManager {
public:
  GameManager();
  void play();

private:
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

  ecs::EntityManager entity_manager_;
  ecs::SystemManager system_manager_;
  sf::Window window_;
};
