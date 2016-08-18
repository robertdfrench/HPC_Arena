#pragma once

#include <unordered_map>
#include <experimental/tuple> // Required for std::apply
#include "entity.h"
#include "Entities/player.h"

namespace ecs {

// Entities should only be created through the manager
class EntityManager {
public:
  EntityManager(): entity_count_{0}, max_bit_position{0} {};

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
    // Construct bit_mask for components
    std::bitset<MAX_COMPONENTS>& mask;
    manager_.set_component_bits<Components...>(system_mask);

    for(auto& kvp : entities_map_) {
      Entity& entity = kvp.second;
      if( entity.has_components(system_mask) ) {
        std::experimental::apply(body, entity.components<Components...>());
      }
    }
  }

  // Set bit of specified component in component_mask
  // Additionally register the component type with the manager if it is not yet
  // Some use of integer_sequence can probably improve this
  template<typename Component>
  void set_component_bit(std::bitset<MAX_COMPONENTS>& component_mask) {
      // Add new component key if not already in map
      const auto pair = unordered_map.emplace(component_key<Component>(), max_bit_position);

      // If new component_key was added we incriment the max bit position
      const bool inserted = pair.second;
      if(inserted)
        max_bit_position++;

      // Update component_mask with new component
      const auto bit_position = *(pair.first->second);
      component_mask.set(bit_position);
  };

  // Recursively handle building maks for multiple components
  template<typename First>
  void set_component_bits(std::bitset<MAX_COMPONENTS>& component_mask) {
    set_component_bit<Components>(component_mask)...;
  };
  template<typename First, typename... Rest>
  void set_component_bits(std::bitset<MAX_COMPONENTS>& component_mask) {
    set_component_bit<First>(component_mask);
    set_component_bits<Rest...>(component_mask);
  };

  // update component_mask by unsetting specified bit
  template<typename Component>
  void unset_component_bit(std::bitset<MAX_COMPONENTS>& component_mask) {
    const auto bit_position = unordered_map_[component_key<T>()];
    component_mask.reset(bit_position);
  };

private:
  uint64_t entity_count_;

  // Map of entity ID to entity object
  std::unordered_map<uint64_t, Entity> entities_map_;

  // Map of component type to bitset bit position
  std::unordered_map<std::type_index, std::size_t bit_position> bit_map_;
  std::size_t max_bit_position;
};

}
