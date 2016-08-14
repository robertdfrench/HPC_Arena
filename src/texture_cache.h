#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>

class TextureCache {
public:
  sf::Texture& get(const std::string& filename);
private:
  // Map to hold texture filename and pointer to texture object
  std::unordered_map<std::string, std::unique_ptr<sf::Texture>> cache_;
};
