#include "lib/chip8.hpp"

namespace chip8_lib {

// todo - handle legacy behavior
Chip8::Chip8(std::string& romPath) {
  uint32_t romSize = this->loadRom(romPath);

  if (romSize > 0) {
    this->mmu = new MMU(this->rom, romSize);
    this->cpu = new Cpu(this->mmu);
  }
}

void Chip8::stepFrame(unsigned int instructionsPerFrame, InputHandler* inputHandler, Renderer* renderer, Synthetizer* synthetizer) {
  // handle input
  for (int i = 0; i < 16; i++) {
    this->mmu->setKeyDown(i, inputHandler->isKeyDown(i));
  }

  // run frame
  for (unsigned int i = 0; i < instructionsPerFrame; i++) {
    this->cpu->tick();
  }

  // render screen
  renderer->render(this->mmu->getScreen());

  // handle sound
  if (this->mmu->getSoundTimer() > 0) {
    synthetizer->play();
  } else {
    synthetizer->stop();
  }

  // decrement timers
  this->mmu->decrementDelayTimer();
  this->mmu->decrementSoundTimer();
}

Chip8::~Chip8() {
  if (this->cpu != nullptr) {
    delete this->cpu;
    this->cpu = nullptr;
  }

  if (this->mmu != nullptr) {
    delete this->mmu;
    this->mmu = nullptr;
  }

  if (this->rom != nullptr) {
    delete this->rom;
    this->rom = nullptr;
  }
}

// will probably extract this method in it's own class
unsigned int Chip8::loadRom(std::string& romPath) {
  std::cout << "Loading: " << romPath << std::endl;

  std::ifstream fileStream(romPath, std::ifstream::binary);
  unsigned int sizeOfFile = 0;

  if (fileStream) {
    fileStream.seekg (0, fileStream.end);
    sizeOfFile = fileStream.tellg();
    fileStream.seekg (0, fileStream.beg);

    this->rom = new uint8_t[sizeOfFile];
    fileStream.read(reinterpret_cast<char*>(this->rom), sizeOfFile);
    fileStream.close();
  } else {
    std::cout << "Could not load rom file" << std::endl;
  }

  return sizeOfFile;
}

}
