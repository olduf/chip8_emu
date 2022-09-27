#pragma once

#include <cstdint>

namespace chip8_lib {

class Renderer
{
public:
  virtual void render(uint8_t* pixelArray) = 0;
  virtual ~Renderer() = default;
};

}
