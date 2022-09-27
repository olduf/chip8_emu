#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>

#include "lib/audio/synthetizer.hpp"
#include "lib/cpu/cpu.hpp"
#include "lib/graphic/renderer.hpp"
#include "lib/input/input_handler.hpp"
#include "lib/memory/mmu.hpp"

namespace chip8_lib {

class Chip8
{
public:
  Chip8(std::string& romPath);
  ~Chip8();

  void stepFrame(unsigned int instructionsPerFrame, InputHandler* inputHandler, Renderer* renderer, Synthetizer* synthetizer);

private:
  unsigned int loadRom(std::string& romPath);

private:
  Cpu* cpu = nullptr;
  MMU* mmu = nullptr;

  Renderer* renderer = nullptr;
  Synthetizer* synthetizer = nullptr;

  uint8_t* rom = nullptr;
};

}
