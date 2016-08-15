#include "game_manager.h"
#include <SFML/Window.hpp>

#include "ECS_core/entity.h"
#include "Entities/player.h"
#include "Systems/movement.h"
#include "Systems/renderer.h"
#include "Systems/boundary.h"

GameManager::GameManager(): window_{sf::VideoMode::getDesktopMode(), "Arena", sf::Style::Fullscreen} {

  window_.setVerticalSyncEnabled(true);

  const int player_count = 1;
  for(int i=0; i<player_count; i++) {
    ecs::Entity& player = add_entity<Player>();
  }

  enable_system<Movement>();
  enable_system<Boundary>(window_.getSize());
  enable_system<Renderer>(window_);
}

void GameManager::play() {
  // run the program as long as the window is open
  while (window_.isOpen()) {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window_.close();
    }

    update_systems(1.0);
  }
}

void process_sf_events() {

}
