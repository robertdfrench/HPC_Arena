#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <bitset>
#include <experimental/tuple> // Required for std::apply
#include "component_base.h"
#include "component.h"

namespace ecs {

const int MAX_COMPONENTS = 64;

// Store all entities and their components

class EntityManager {
private:
  // Each element of components_ is a vector of a particular component type
  // To get the vector of Position component*'s': components_[Position::type_id()]
  std::array<
               std::vector< std::unique_ptr<ComponentBase> >,
               MAX_COMPONENTS
             > components_;

  // Each element of component_indicies_ is an array of indices indicating
  // Where in the components_[] vector an entities component lives
  // component_indicies_[entity_id][component_type_index] =  index in components_[type]
  std::vector< std::array<std::size_t, MAX_COMPONENTS> > component_indices_;

  // Each element of component_mask_ is a bitset of the entities components
  // component_mask_[entity_id] = mask of entity_id's component types
  std::vector< std::bitset<MAX_COMPONENTS> > component_masks_;

public:

  int entity_count() {
    return component_masks_.size();
  }

  int new_entity() {
    const int entity_count = this->entity_count();
    component_indices_.emplace_back();
    component_masks_.emplace_back();
    return entity_count;
  }

  // Add component T to entity with id_
  template<typename T>
  void add_component(int entity_id) {
    const auto component_id = T::type_id();

    // Add new component of type T
    components_[component_id].emplace_back(std::make_unique<T>());

    // Add index of inserted component to lookup
    const auto component_index = components_[component_id].size() - 1;
    component_indices_[entity_id][component_id] = component_index;

    // Update entities component mask
    component_masks_[entity_id].set(component_id);
  }

  // Remove component T to entity with id_
  template<typename T>
  void remove_component(int id) {
    // PUT STUFF" HERE
  }

  // fetch reference to component T
  template<typename T>
  T& fetch_component(int entity_id) {
    const auto component_id = T::type_id();
    const auto component_index = component_indices_[entity_id][component_id];
    return *(static_cast<T*>(components_[component_id][component_index].get()));
  }

  // fetch tuple of reference to components Components...
  template<typename... Components>
  auto fetch_components(int entity_id) {
    return std::forward_as_tuple(this->fetch_component<Components>(entity_id)...);
  }

  // Test if entity has specified components
  template<typename... Components>
  bool has_components(int entity_id) {
    std::bitset<MAX_COMPONENTS> test_bits;

    // Call test_bits.set(T::type_id()) for each component in Components...
    [](...){}((test_bits.set(Components::type_id()))...); // I'm 80% sure this works

    return (test_bits & component_masks_[entity_id]) == test_bits;
  }

  // Iterate through entity ID's and apply body lambda to those maching Component types
  template<typename... Components, typename Body>
  void for_each(Body body) {
    for(int id=0; id<entity_count(); id++) {
      if( has_components<Components...>(id) ) {
        std::experimental::apply(body, fetch_components<Components...>(id));
      }
    }
  }

};
}
