#pragma once

#include <SFML/Graphics.hpp>
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

  template<typename SystemType, typename... Args>
  void enable_system(Args&&... args) {
    system_manager_.enable<SystemType>(args...);
  }

  void update_systems(float dt) {
    system_manager_.update(entity_manager_, dt);
  }

  void process_sf_events();

  ecs::EntityManager entity_manager_;
  ecs::SystemManager system_manager_;
  sf::RenderWindow window_;
};
