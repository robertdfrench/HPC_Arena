#pragma once

#include "ECS_core/component.h"
#include "SFML/System/Vector2.hpp"

struct Position: public sf::Vector2<float>, public ecs::Component<Position> {};
