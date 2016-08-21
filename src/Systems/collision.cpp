#include <cmath>
#include "collision.h"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "ECS_core/entity_manager.h"
#include "Components/position.h"
#include "Components/collision_bounds.h"

Collision::Collision(sf::Vector2u screen_dims, int spacing) {
  bin_spacing_ = spacing;

  // Collision grid dimensions
  sf::Vector2u grid_dim((unsigned int)std::ceil(screen_dims.x / (float)spacing),
                        (unsigned int)std::ceil(screen_dims.y / (float)spacing)
  );

  // Allocate grid
  grid_.reserve(grid_dim.y);
  for(auto& row : grid_)
    row.reserve(grid_dim.x);
}

void Collision::update(ecs::EntityManager& entity_manager, float dt) {
  // Reset collision grid
  for(auto& row : grid_) {
    for(auto& cell : row) {
      cell.clear();
    }
  }

  // Place entities in appropriate bins
  entity_manager.for_each_with_id<Position, CollisionBounds>([this, dt] (int entity_id,
                                                                    Position& position,
                                                                    CollisionBounds& collision_bounds) {
    //
    // Place each corner of bounding box in collision grid bin
    //

    // Calculate corners of collision bounding box
    const int bounds_width = collision_bounds.size.x;
    const int bounds_height = collision_bounds.size.y;
    const int upper_left_x = static_cast<int>(position.x - bounds_width/2.0);
    const int upper_left_y = static_cast<int>(position.y - bounds_height/2.0);

    // Upper left
    const int bin_ul_x = upper_left_x/bin_spacing_;
    const int bin_ul_y = upper_left_y/bin_spacing_;
    // Upper right
    const int bin_ur_x = (upper_left_x + bounds_width) / bin_spacing_;
    const int bin_ur_y = bin_ul_y;
    // Lower right
    const int bin_lr_x = bin_ur_x;
    const int bin_lr_y = (upper_left_y - bounds_height) / bin_spacing_;
    // Lower left
    const int bin_ll_x = bin_ul_x;
    const int bin_ll_y = (bin_ul_y - bounds_height) / bin_spacing_;

    // Add entities ID to each grid bin it's in
    // Make sure not to add entity multiple times to grid bin
    grid_[bin_ul_y][bin_ul_x].emplace_back(entity_id);

    if(bin_ur_x != bin_ul_x)
      grid_[bin_ur_y][bin_ur_x].emplace_back(entity_id);
    if(bin_lr_y != bin_ur_y)
      grid_[bin_lr_y][bin_lr_x].emplace_back(entity_id);
    if(bin_ll_y != bin_ul_y)
      grid_[bin_ll_y][bin_ll_x].emplace_back(entity_id);
  });

  // Loop over grid and detect collisions, add collided component which holds entity collided with
  // something something don't duplicate collisions
  int collisions =0;
  for(auto& row : grid_) {
    for(auto& cell : row) {
      if(cell.size())
        collisions++;
    }
  }
  std::cout<<"entities in cells: "<<collisions<<std::endl;
  /*

    // Apply damage to entities that have collided that have health
    // Or if both entities have health move them apart
    entity_manager.for_each<Collided, Health>([dt] (Collided& collided, Health& health) {

    });

    // Remove damage causing entities if they've collided with an entity having health
    entity_manager.for_each<Collided, Damage>([dt] (Collided& collided, Health& health) {

    });
    */
};