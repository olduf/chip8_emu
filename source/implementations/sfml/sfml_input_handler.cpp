#include "implementations/sfml/sfml_input_handler.hpp"
#include <iostream>

bool SFMLInputHandler::isKeyDown(uint8_t key) {
  return sf::Keyboard::isKeyPressed(this->keyMapping[key & 0x0F]);
}
