#include <iostream>
#include "ECS_core/ecs_manager.h"
#include "Entities/player.h"
#include "Systems/movement.h"

int main(int argc, char** argv) {
  ecs::EcsManager game;

  const int player_count = 10000;

  for(int i=0; i<player_count; i++) {
    ecs::Entity& player = game.add_entity<Player>();
  }

  game.enable_system<Movement>();

  for(int i=0; i<60; i++) {
    game.update_systems(1.0);
  }

}
