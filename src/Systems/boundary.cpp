#include "Components/position.h"
#include "Components/sprite.h"
#include "ECS_core/entity_manager.h"
#include "boundary.h"

void Boundary::update(ecs::EntityManager& entity_manager, float dt) {
  entity_manager.for_each<Position, Sprite>([this, dt] (Position& position, Sprite& sprite) {
    if(position.x < 0)
      position.x = 0;
    else if(position.x > (size_.x - sprite.size.x))
      position.x = size_.x - sprite.size.x;
    if(position.y < 0)
      position.y = 0;
    else if(position.y > (size_.y - sprite.size.y))
      position.y = size_.y - sprite.size.y;
  });
};
