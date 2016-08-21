#include "texture_cache.h"

sf::Texture& TextureCache::get(const std::string& filename) {
  const bool cached = cache_.count(filename);

  if(cached) {
    return *cache_[filename];
  }
  else {
    const auto pair = cache_.emplace(filename, std::make_unique<sf::Texture>());
    sf::Texture& texture = *(pair.first->second);
    texture.loadFromFile(filename);
    return texture;
  }
}
