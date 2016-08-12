#pragma once

#include <vector>
#include "entity_manager.h"

namespace ecs {

class System {
public:
  virtual void update(EntityManager& entity_manager, float dt) = 0;
};
}
