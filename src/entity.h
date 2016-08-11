#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <experimental/tuple> // Required for std::apply
#include "component.h"

namespace EntitySystem {

using EntityID = uint64_t;

// Components are mapped with their type as the key
template<typename T>
constexpr std::type_index component_key() {
  return std::type_index(typeid(T));
}

// Entities may only have a single component of a given type
class Entity {
private:
  const EntityID id_;
  std::unordered_map <std::type_index,
                      std::unique_ptr<Component> > components_;

public:
  Entity(EntityID id): id_{id} {};

  // Create component of type T and add to entity
  // ent.add<Position>();
  template<typename T>
  void add() {
    components_[component_key<T>()] = std::make_unique<T>();
  }

  // Remove component of type T from entity and delete it
  // ent.remove<Position>();
  template<typename T>
  void remove() {
    components_.erase(component_key<T>());
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

  // Pop off key and test if entity includes it, recurse
  // Note Current and Next are needed so there is no ambiguity when Rest is 0 length
  template<typename Current, typename Next, typename... Rest>
  bool has() {
    bool has_current = components_.count(component_key<Current>());
    return has_current ? has<Next, Rest...>() : false;
  }
  // Handle last test and end of recursion
  template<typename Last>
  bool has() {
    const auto key = std::type_index(component_key<Last>());
    bool has_last = components_.count(key);
    return has_last;
  }

};

}
