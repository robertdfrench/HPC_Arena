#pragma once

#include "entity_manager.h"
#include "system.h"

namespace ecs {


// Hold all game systems
class SystemManager {
public:

  // Add a system to managed systems
  template<typename Sys, typename... Args>
  void enable(Args&&... args) {
    systems_.push_back( std::make_unique<Sys>(args...) );
  }

  // Update all game systems
  void update(EntityManager &entity_manager, float dt) {
    for(auto& system : systems_) {
      system->update(entity_manager, dt);
    }
  }

private:
  std::vector< std::unique_ptr< System> > systems_;
};

}
