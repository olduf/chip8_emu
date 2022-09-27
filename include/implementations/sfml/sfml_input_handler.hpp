#pragma once

#include <SFML/Graphics.hpp>
#include "lib/input/input_handler.hpp"

class SFMLInputHandler : public chip8_lib::InputHandler
{
public:
  virtual ~SFMLInputHandler() = default;

  bool isKeyDown(uint8_t key);

private:
  // TODO - make configurable
  sf::Keyboard::Key keyMapping[16] = {
    sf::Keyboard::Key::X,
    sf::Keyboard::Key::Num1,
    sf::Keyboard::Key::Num2,
    sf::Keyboard::Key::Num3,
    sf::Keyboard::Key::Q,
    sf::Keyboard::Key::W,
    sf::Keyboard::Key::E,
    sf::Keyboard::Key::A,
    sf::Keyboard::Key::S,
    sf::Keyboard::Key::D,
    sf::Keyboard::Key::Z,
    sf::Keyboard::Key::C,
    sf::Keyboard::Key::Num4,
    sf::Keyboard::Key::R,
    sf::Keyboard::Key::F,
    sf::Keyboard::Key::V
  };
};
