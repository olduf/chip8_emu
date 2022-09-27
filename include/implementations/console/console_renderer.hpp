#pragma once

#include <iostream>
#include "lib/graphic/renderer.hpp"

class ConsoleRenderer : public chip8_lib::Renderer
{
public:
  ConsoleRenderer() = default;
  virtual ~ConsoleRenderer() = default;

  void render(uint8_t* pixelArray);
};
