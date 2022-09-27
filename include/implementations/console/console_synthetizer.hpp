#pragma once

#include <iostream>
#include "lib/audio/synthetizer.hpp"

class ConsoleSynthetizer : public chip8_lib::Synthetizer
{
public:
  virtual ~ConsoleSynthetizer() = default;

  void play() {}
  void stop() {}
};
