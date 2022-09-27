#pragma once

namespace chip8_lib {

class Synthetizer
{
public:
  virtual ~Synthetizer() = default;

  virtual void play() = 0;
  virtual void stop() = 0;
};

}
