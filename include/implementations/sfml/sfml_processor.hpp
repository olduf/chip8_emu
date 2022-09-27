#pragma once

#include "lib/processor.hpp"
#include "implementations/sfml/sfml_input_handler.hpp"
#include "implementations/sfml/sfml_renderer.hpp"
#include "implementations/sfml/sfml_synthetizer.hpp"

const unsigned int SCREEN_WIDTH = 1080;
const unsigned int SCREEN_HEIGHT = 768;
const float SCALE = 12.f;
const sf::Color BACKGROUND_COLOR(0x64, 0x95, 0xED);
const sf::Time FRAME_TIME = sf::microseconds(16666);

class SFMLProcessor : public chip8_lib::Processor
{
public:
  SFMLProcessor();
  virtual ~SFMLProcessor();

  int start(chip8_lib::Chip8* chip8);

protected:
  void handleTiming();
  chip8_lib::InputHandler* getInputHandler();
  chip8_lib::Renderer* getRenderer();
  chip8_lib::Synthetizer* getSynthetizer();

private:
  sf::Clock clock;
  sf::RenderWindow* window = nullptr;

  SFMLInputHandler* inputHandler = nullptr;
  SFMLRenderer* renderer = nullptr;
  SFMLSynthetizer* synthetizer = nullptr;
};
