#include "texture_cache.h"

sf::Texture& TextureCache::get(const std::string& filename) {
  const auto pair = cache_.emplace(filename, std::make_unique<sf::Texture>());
  sf::Texture& texture = *(pair.first->second);
  const bool inserted = pair.second; // true if new texture inserted into cache

  if(inserted)
    texture.loadFromFile(filename);

  return texture;
}
