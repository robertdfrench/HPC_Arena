#include "player_builder.h"
#include "ECS_core/entity.h"

static ecs::Entity& Player::build(ecs::Entity& player) {
  player.add<Position>();
  player.add<Velocity>();

  player.component<Position>().x = 0.0;
  player.component<Position>().y = 0.0;

  player.component<Velocity>().x = 1.0;
  player.component<Velocity>().y = 1.0;

  return player;
}
