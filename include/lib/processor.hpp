#pragma once

#include "lib/chip8.hpp"
#include "lib/audio/synthetizer.hpp"
#include "lib/graphic/renderer.hpp"
#include "lib/input/input_handler.hpp"

namespace chip8_lib {

class Processor
{
public:
  virtual ~Processor() = default;

protected:
  void run(chip8_lib::Chip8* chip8);

  virtual void handleTiming() = 0;
  virtual InputHandler* getInputHandler() = 0;
  virtual Renderer* getRenderer() = 0;
  virtual Synthetizer* getSynthetizer() = 0;

protected:
  bool frameProcessed;

private:
  unsigned int instructionsPerFrame = 10;
  // maybe an enum for this? -> 420Hz: 7, 480Hz: 8, 540Hz: 9, 600Hz: 10, 660Hz: 11, 720Hz: 12, 780Hz: 13
  // in steps of 60Hz to facilitate frame speed
};

}
