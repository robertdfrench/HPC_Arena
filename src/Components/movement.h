#pragma once

struct Position: public sf::Vector2<float>, public es::Component {};
struct Velocity: public sf::Vector2<float>, public es::Component {};
