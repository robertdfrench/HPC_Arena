#pragma once

#include <unordered_map>
#include <experimental/tuple> // Required for std::apply
#include "entity.h"
#include "Entities/player.h"

namespace ecs {

// Entities should only be created through the manager
class EntityManager {
public:
  EntityManager(): entity_count_{0} {};

  // Create entity from builder and add to manager
  template<typename Builder>
  Entity& create() {
    const uint64_t entity_id = entity_count_;
    entities_map_.emplace(entity_id, entity_id);
    Entity& new_entity = entities_map_.at(entity_id);
    Builder::build(new_entity);
    entity_count_++;
    return new_entity;
  }

  // Iterate through entities and apply body lambda to those maching Component types
  template<typename... Components, typename Body>
  void for_each(Body body) {
    for(auto& kvp : entities_map_) {
      Entity& entity = kvp.second;
      if( entity.has<Components...>() ) {
        // Requires C++17
        std::experimental::apply(body, entity.components<Components...>());
      }
    }
  }

private:
  uint64_t entity_count_;
  std::unordered_map<uint64_t, Entity> entities_map_;
};

}
