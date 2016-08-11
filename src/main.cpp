#include <iostream>
#include "game_master.h"
#include <ctime>

namespace ES = EntitySystem;

struct Position: public ES::Component {
  float x, y;
};
struct Velocity: public ES::Component {
  float x, y;
};
struct Acceleration: public ES::Component {
  float x, y;
};

class MovementSystem: public ES::System {

  void update(ES::EntityManager& entity_manager, float dt) override {
    entity_manager.for_each<Position, Velocity>([dt] (Position& position, Velocity& velocity) {
      position.x += velocity.x*dt;
      position.y += velocity.y*dt;
    });
  };

};

int main(int argc, char** argv) {
  ES::GameMaster game;

  const int player_count = 10000;

  for(int i=0; i<player_count; i++) {
    ES::Entity& ent = game.add_entity();
    ent.add<Position>();
    ent.add<Velocity>();
    ent.add<Acceleration>();

    ent.component<Position>().x = 0.0;
    ent.component<Position>().y = 0.0;
    ent.component<Acceleration>().x = 0.0;
    ent.component<Acceleration>().y = 0.0;
    ent.component<Velocity>().x = 1.0;
    ent.component<Velocity>().y = 1.0;
  }

  game.enable_system<MovementSystem>();

  std::clock_t start;
  double duration;
  start = std::clock();

  for(int i=0; i<60; i++) {
    game.update_systems(1.0);
  }

  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  std::cout<<"loop time: "<< duration <<'\n';
}
