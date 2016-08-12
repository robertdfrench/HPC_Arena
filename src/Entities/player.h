#pragma once

#include "ECS_core/entity.h"

class Player {
public:
  static ecs::Entity& build(ecs::Entity& entity);
};
