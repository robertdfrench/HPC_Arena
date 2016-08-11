#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <experimental/tuple> // Required for std::apply
#include <vector>
#include "component.h"

// Entities may only have a single component of a given type
class Entity {
private:
  const uint64_t id_;
  std::unordered_map <std::type_index,
                      std::unique_ptr<Component> > components_;

public:
  Entity(uint64_t id): id_{id} {};

  // Create component of type T and add to entity
  // ent.add<Position>();
  template<typename T>
  void add() {
    components_[std::type_index(typeid(T))] = std::make_unique<T>();
  }

  // Remove component of type T from entity and delete it
  // ent.remove<Position>();
  template<typename T>
  void remove() {
    components_.erase(std::type_index(typeid(T)));
  }

  // Return a reference to the component of the specified template type
  // ent.component<Position>()
  template<typename T>
  T& component() {
    // Could use static_cast as well
    return *(static_cast<T*>(
                             (components_[std::type_index(typeid(T))]).get()
                           ));
  }

  // Return references to the components of the specified template types
  // ent.components<Position, Velocity>()
  template<typename... Components>
  auto components() {
    return std::forward_as_tuple(this->component<Components>()...);
  }

  // Determine if entity has all of the specified components
  // Can't loop through variadic template components so we use recursion

  // Pop off key and test if entity includes it, recurse
  // Note Current and Next are needed so there is no ambiguity when Rest is 0 length
  template<typename Current, typename Next, typename... Rest>
  bool has() {
    const auto key = std::type_index(typeid(Current));
    bool has_current = components_.count(key);
    return has_current ? has<Next, Rest...>() : false;
  }
  // Handle last test and end of recursion
  template<typename Last>
  bool has() {
    const auto key = std::type_index(typeid(Last));
    bool has_last = components_.count(key);
    return has_last;
  }

};

// Entities should only be created through the manager
class EntityManager {
public:
  EntityManager(): entity_count_{0} {};

  // Create and add entity to manager
  Entity& create() {
    // todo: improve this so it's dynamic and entities removed
    const uint64_t entity_id = entity_count_;
    entities_map_.emplace(entity_id, entity_id);
    entity_count_++;
    return entities_map_.at(entity_id);
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
