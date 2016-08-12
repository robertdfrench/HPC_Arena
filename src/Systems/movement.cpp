#include "movement.h"
#include "ECS_core/system_manager.h"
#include "ECS_core/entity_manager.h"

void Movement::update(ecs::EntityManager& entity_manager, float dt) override {
  entity_manager.for_each<Position, Velocity>([dt] (Position& position, Velocity& velocity) {
    position += velocity * dt;
  });
};
