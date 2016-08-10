#pragma once

#include <vector>
#include "entity.h"

class System {
  public:
  virtual void update(EntityManager& entity_manager, float dt) = 0;
};

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
