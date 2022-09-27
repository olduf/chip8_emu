#include "implementations/sfml/sfml_renderer.hpp"

SFMLRenderer::SFMLRenderer(unsigned int screenWidth, unsigned int screenHeight, float scale) {
  this->texture.create(64, 32);

  this->sprite.setTexture(this->texture);
  this->sprite.setPosition(sf::Vector2f((screenWidth - (64 * scale)) / 2 , (screenHeight - (32 * scale)) / 2));
  this->sprite.setScale(sf::Vector2f(scale, scale));

  this->texture.update(this->frameBuffer);
}

sf::Sprite& SFMLRenderer::getSprite() {
  return this->sprite;
}

void SFMLRenderer::render(uint8_t* pixelArray) {
  for (int i = 0; i < 32 * 64; i++) {
    uint8_t value = pixelArray[i] == 0 ? 0 : 0xFF;
    unsigned int index = i * 4;

    this->frameBuffer[index] = value;
    this->frameBuffer[index + 1] = value;
    this->frameBuffer[index + 2] = value;
    this->frameBuffer[index + 3] = 0xFF;
  }

  this->texture.update(this->frameBuffer);
}
