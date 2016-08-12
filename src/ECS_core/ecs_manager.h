#pragma once

#include "entity_manager.h"
#include "system_manager.h"

namespace ecs {

// Control the entity and system managers
class EcsManager {
public:
  template<typename EntityType>
  Entity& add_entity() {
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
  EntityManager entity_manager_;
  SystemManager system_manager_;
};

}
