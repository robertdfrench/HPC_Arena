#include "texture_cache.h"

sf::Texture& TextureCache::get(const std::string& filename) {
  const auto pair = cache_.emplace(filename, std::make_unique<sf::Texture>());
  sf::Texture& texture = *((*pair.first).second);
  const bool exists = pair.second;

  if(!exists)
    texture.loadFromFile(filename);

  return texture;
}
