#pragma once

#include <cstdint>

namespace chip8_lib {

class InputHandler
{
public:
  virtual ~InputHandler() = default;

  virtual bool isKeyDown(uint8_t key) = 0;
};

}
