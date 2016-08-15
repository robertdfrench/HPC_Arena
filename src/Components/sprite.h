#pragma once

#include "ECS_core/component.h"
#include "SFML/System/Vector2.hpp"
#include <string>

struct Sprite: public ecs::Component {
  std::string filename;
  sf::Vector2u size;
  int depth_layer = 0;
};
