#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <experimental/tuple> // Required for std::apply
#include "component.h"
#include "entity_manager.h"

namespace ecs {

using EntityID = uint64_t;

// Components are mapped with their type as the key
template<typename T>
std::type_index component_key() {
  return std::type_index(typeid(T));
}

// Entities may only have a single component of a given type
class Entity {
private:
  const EntityID id_;
  EntityManager& manager_;
  std::unordered_map <std::type_index,
                      std::unique_ptr<Component> > components_;
  std::bitset<MAX_COMPONENTS> component_mask_;

public:
  Entity(EntityID id, EntityManager& manager): id_{id}, manager_{manager} {};

  // Create component of type T and add to entity
  // ent.add<Position>();
  template<typename T>
  void add() {
    components_[component_key<T>()] = std::make_unique<T>();

    // Register component type so bitfield entry can be created
    // and component_mask of entity updated
    manager_.set_component_bit<T>(component_mask_);
  }

  // Remove component of type T from entity and delete it
  // ent.remove<Position>();
  template<typename T>
  void remove() {
    components_.erase(component_key<T>());

    manager_.unset_component_bit<T>(component_mask_);
  }

  // Return a reference to the component of the specified template type
  // ent.component<Position>()
  template<typename T>
  T& component() {
    // Could use static_cast as well
    return *(static_cast<T*>(
                             (components_[component_key<T>()]).get()
                           ));
  }

  // Return references to the components of the specified template types
  // ent.components<Position, Velocity>()
  template<typename... Components>
  auto components() {
    return std::forward_as_tuple(this->component<Components>()...);
  }

  // Determine if entity has all of the specified components
  bool has_components(std::bitset<MAX_COMPONENTS>& mask) {
    return mask == component_mask_;
  }
};

}
