#include "lib/processor.hpp"

namespace chip8_lib {

void Processor::run(chip8_lib::Chip8* chip8) {
  if (!this->frameProcessed) {
    chip8->stepFrame(this->instructionsPerFrame, this->getInputHandler(), this->getRenderer(), this->getSynthetizer());
    this->frameProcessed = true;
  }

  this->handleTiming();
}

}
