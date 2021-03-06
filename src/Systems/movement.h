#pragma once

#include "ECS_core/system.h"
#include "ECS_core/entity_manager.h"

class Movement: public ecs::System {
  void update(ecs::EntityManager& entity_manager, float dt) override;
};
