#include <iostream>
#include "game_master.h"
#include "component.h"
#include "entity.h"

struct Position: public Component {
  float x, y;
};
struct Velocity: public Component {
  float x, y;
};
struct Acceleration: public Component {
  float x, y;
};

class MovementSystem: public System {

  void update(EntityManager& entity_manager, float dt) override {
    entity_manager.for_each<Position, Velocity>([dt] (Position& position, Velocity& velocity) {
      position.x += velocity.x*dt;
      position.y += velocity.y*dt;
    });
  };

};

int main(int argc, char** argv) {
  GameMaster game;

  Entity& player = game.add_entity();
  player.add<Position>();
  player.add<Velocity>();
  player.add<Acceleration>();

  player.component<Position>().x = 0.0;
  player.component<Position>().y = 0.0;
  player.component<Acceleration>().x = 0.0;
  player.component<Acceleration>().y = 0.0;
  player.component<Velocity>().x = 1.0;
  player.component<Velocity>().y = 1.0;

  std::cout<<player.component<Position>().x << std::endl;
  std::cout<<player.component<Position>().y << std::endl;
  std::cout<<player.component<Velocity>().x << std::endl;
  std::cout<<player.component<Velocity>().y << std::endl;
  std::cout<<player.component<Acceleration>().x << std::endl;
  std::cout<<player.component<Acceleration>().y << std::endl;

  game.enable_system<MovementSystem>();

  for(int i=0; i<10; i++) {
    game.update_systems(1.0);
  }

  std::cout<<player.component<Position>().x << std::endl;
  std::cout<<player.component<Position>().y << std::endl;
  std::cout<<player.component<Velocity>().x << std::endl;
  std::cout<<player.component<Velocity>().y << std::endl;
  std::cout<<player.component<Acceleration>().x << std::endl;
  std::cout<<player.component<Acceleration>().y << std::endl;

}
