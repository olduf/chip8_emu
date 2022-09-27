#pragma once

#include <SFML/Graphics.hpp>
#include "lib/graphic/renderer.hpp"

class SFMLRenderer : public chip8_lib::Renderer
{
public:
  SFMLRenderer(unsigned int screenWidth, unsigned int screenHeight, float scale);
  virtual ~SFMLRenderer() = default;

  void render(uint8_t* pixelArray);

  sf::Sprite& getSprite();

private:
  sf::Sprite sprite;
  sf::Texture texture;
  uint8_t frameBuffer[64 * 32 * 4];
};
