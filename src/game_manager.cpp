#include "game_manager.h"
#include <SFML/Window.hpp>

#include "ECS_core/entity.h"
#include "Entities/player.h"
#include "Systems/movement.h"

GameManager::GameManager(): window_{sf::VideoMode(800, 600), "Arena"} {
  const int player_count = 10000;

  for(int i=0; i<player_count; i++) {
    ecs::Entity& player = add_entity<Player>();
  }

  enable_system<Movement>();
}

void GameManager::play() {
  for(int i=0; i<60; i++) {
    update_systems(1.0);
  }
}
