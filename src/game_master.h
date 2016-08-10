#pragma once

#include "entity.h"
#include "system.h"

// Control the entity and system managers
class GameMaster {
public:
  Entity& add_entity() {
    return entity_manager_.create();
  }

  template<typename System>
  void enable_system() {
    system_manager_.enable<System>();
  }

  void update_systems(float dt) {
    system_manager_.update(entity_manager_, dt);
  }

private:
  EntityManager entity_manager_;
  SystemManager system_manager_;
};
