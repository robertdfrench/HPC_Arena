#include <iostream>
#include "game_manager.h"
#include "ECS_core/entity.h"
#include "Entities/player.h"
#include "Systems/movement.h"

int main(int argc, char** argv) {
  GameManager game;

  const int player_count = 10000;

  for(int i=0; i<player_count; i++) {
    ecs::Entity& player = game.add_entity<Player>();
  }

  game.enable_system<Movement>();

  for(int i=0; i<60; i++) {
    game.update_systems(1.0);
  }
}
