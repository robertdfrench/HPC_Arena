#pragma once

#include "ECS_core/entity.h"
#include "ECS_core/entity_manager.h"

class Player {
public:
  static ecs::Entity& build(ecs::EntityManager& entity_manager);
};
