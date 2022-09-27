#pragma once

#include <cstdint>
#include <cstdlib>
#include <functional>
#include "lib/cpu/registers.hpp"
#include "lib/memory/mmu.hpp"

namespace chip8_lib {

class Instruction {
public:
  static const Instruction _00E0;
  static const Instruction _00EE;
  static const Instruction _1nnn;
  static const Instruction _2nnn;
  static const Instruction _3xnn;
  static const Instruction _4xnn;
  static const Instruction _5xy0;
  static const Instruction _6xnn;
  static const Instruction _7xnn;
  static const Instruction _8xy0;
  static const Instruction _8xy1;
  static const Instruction _8xy2;
  static const Instruction _8xy3;
  static const Instruction _8xy4;
  static const Instruction _8xy5;
  static const Instruction _8xy6;
  static const Instruction _8xy7;
  static const Instruction _8xyE;
  static const Instruction _9xy0;
  static const Instruction _Annn;
  static const Instruction _Bnnn;
  static const Instruction _Cxnn;
  static const Instruction _Dxyn;
  static const Instruction _Ex9E;
  static const Instruction _ExA1;
  static const Instruction _Fx07;
  static const Instruction _Fx0A;
  static const Instruction _Fx15;
  static const Instruction _Fx18;
  static const Instruction _Fx1E;
  static const Instruction _Fx29;
  static const Instruction _Fx33;
  static const Instruction _Fx55;
  static const Instruction _Fx65;

  void execute(Registers* registers, MMU* mmu, uint16_t opCode) const;

private:
  Instruction(std::function<void(Registers*, MMU*, uint16_t)> operation);

  std::function<void(Registers*, MMU*, uint16_t)> operation;
};

}
