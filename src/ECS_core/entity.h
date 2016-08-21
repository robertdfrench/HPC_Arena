#pragma once

#include "entity_manager.h"

// Wrapper class to act create entity handles
// Allows us to treat entities as regular objects

namespace ecs {

class Entity {
private:
  int id_;
  EntityManager& manager_;
public:
  // Entities should only be created through the entity_manager
  Entity(EntityManager& manager, int id): manager_{manager}, id_{id} {}

  // destroy entity
  void destroy() {
    manager_.invalidate_entity(id_);
  }

  // Add component T to entity
  template<typename T>
  void add_component() {
    return manager_.add_component<T>(id_);
  }

  // Remove component T from entity
  template<typename T>
  void remove_component() {
    return manager_.remove_component<T>(id_);
  }

  // fetch reference to component T
  template<typename T>
  T& component() {
    return manager_.fetch_component<T>(id_);
  }

  // fetch tuple of reference to components Components...
  template<typename... Components>
  auto components() {
    return manager_.fetch_components<Components...>(id_);
  }

  // Test if entity has specified components
  template<typename... Components>
  bool has_components() {
    return manager_.has_components<Components...>(id_);
  }

};
}
