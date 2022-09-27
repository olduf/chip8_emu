#include "lib/cpu/instruction.hpp"

namespace chip8_lib {

Instruction::Instruction(std::function<void(Registers*, MMU*, uint16_t)> operation) {
  this->operation = operation;
}

void Instruction::execute(Registers* registers, MMU* mmu, uint16_t opCode) const {
  this->operation(registers, mmu, opCode);
}

const Instruction Instruction::_00E0([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t* pixelArray = mmu->getScreen();

  for (size_t i = 0; i < 32 * 64; i++) {
    pixelArray[i] = 0;
  }
});

const Instruction Instruction::_00EE([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  registers->pc = mmu->popStack() & 0x0FFF;
});

const Instruction Instruction::_1nnn([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  registers->pc = opCode & 0x0FFF;
});

const Instruction Instruction::_2nnn([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  mmu->pushOnStack(registers->pc);
  registers->pc = opCode & 0x0FFF;
});

const Instruction Instruction::_3xnn([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;
  uint8_t value = opCode & 0x00FF;

  if (registers->vx[index] == value) {
    registers->pc += 2;
  }
});

const Instruction Instruction::_4xnn([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;
  uint8_t value = opCode & 0x00FF;

  if (registers->vx[index] != value) {
    registers->pc += 2;
  }
});

const Instruction Instruction::_5xy0([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t xIndex = (opCode & 0x0F00) >> 8;
  uint8_t yIndex = (opCode & 0x00F0) >> 4;

  if (registers->vx[xIndex] == registers->vx[yIndex]) {
    registers->pc += 2;
  }
});

const Instruction Instruction::_6xnn([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;
  registers->vx[index] = opCode & 0x00FF;
});

const Instruction Instruction::_7xnn([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;
  // we do not set the carry flag here
  registers->vx[index] += (opCode & 0x00FF);
});

const Instruction Instruction::_8xy0([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t xIndex = (opCode & 0x0F00) >> 8;
  uint8_t yIndex = (opCode & 0x00F0) >> 4;

  registers->vx[xIndex] = registers->vx[yIndex];
});

const Instruction Instruction::_8xy1([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t xIndex = (opCode & 0x0F00) >> 8;
  uint8_t yIndex = (opCode & 0x00F0) >> 4;

  registers->vx[xIndex] |= registers->vx[yIndex];
});

const Instruction Instruction::_8xy2([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t xIndex = (opCode & 0x0F00) >> 8;
  uint8_t yIndex = (opCode & 0x00F0) >> 4;

  registers->vx[xIndex] &= registers->vx[yIndex];
});

const Instruction Instruction::_8xy3([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t xIndex = (opCode & 0x0F00) >> 8;
  uint8_t yIndex = (opCode & 0x00F0) >> 4;

  registers->vx[xIndex] ^= registers->vx[yIndex];
});

const Instruction Instruction::_8xy4([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t xIndex = (opCode & 0x0F00) >> 8;
  uint8_t yIndex = (opCode & 0x00F0) >> 4;
  uint8_t oldValue = registers->vx[xIndex];
  uint8_t carryFlag = 0;

  registers->vx[xIndex] += registers->vx[yIndex];

  if (registers->vx[xIndex] < oldValue) {
    carryFlag = 1;
  }

  registers->vx[0xF] = carryFlag;
});

const Instruction Instruction::_8xy5([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t xIndex = (opCode & 0x0F00) >> 8;
  uint8_t yIndex = (opCode & 0x00F0) >> 4;
  uint8_t carryFlag = 1;

  if (registers->vx[yIndex] > registers->vx[xIndex]) {
    carryFlag = 0;
  }

  registers->vx[xIndex] = registers->vx[xIndex] - registers->vx[yIndex];
  registers->vx[0xF] = carryFlag;
});

const Instruction Instruction::_8xy6([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;

  registers->vx[0xF] = registers->vx[index] & 0b00000001;
  registers->vx[index] >>= 1;
});

const Instruction Instruction::_8xy7([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t xIndex = (opCode & 0x0F00) >> 8;
  uint8_t yIndex = (opCode & 0x00F0) >> 4;
  uint8_t carryFlag = 1;

  if (registers->vx[xIndex] > registers->vx[yIndex]) {
    carryFlag = 0;
  }

  registers->vx[xIndex] = registers->vx[yIndex] - registers->vx[xIndex];
  registers->vx[0xF] = carryFlag;
});

const Instruction Instruction::_8xyE([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;

  registers->vx[0xF] = (registers->vx[index] & 0b10000000) >> 7;
  registers->vx[index] <<= 1;
});

const Instruction Instruction::_9xy0([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t xIndex = (opCode & 0x0F00) >> 8;
  uint8_t yIndex = (opCode & 0x00F0) >> 4;

  if (registers->vx[xIndex] != registers->vx[yIndex]) {
    registers->pc += 2;
  }
});

const Instruction Instruction::_Annn([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  registers->I = opCode & 0x0FFF;
});

const Instruction Instruction::_Bnnn([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  registers->pc = (opCode & 0x0FFF) + registers->vx[0];
});

const Instruction Instruction::_Cxnn([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;
  uint8_t modulo = opCode & 0x00FF;

  registers->vx[index] = (rand() % 0xFF) & modulo;
});

const Instruction Instruction::_Dxyn([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t* pixelArray = mmu->getScreen();
  uint8_t x = registers->vx[(opCode & 0x0F00) >> 8] % 64;
  uint8_t y = registers->vx[(opCode & 0x00F0) >> 4] % 32;
  uint8_t n = opCode & 0x000F;

  // reset carry flag
  registers->vx[0xF] = 0;

  for (int j = 0; j < n; j++) {
    uint8_t pixel = mmu->getByte(registers->I + j);

    for (int i = 0; i < 8; i++) {
      if ((pixel & (0x80 >> i)) != 0) {
        uint16_t index = x + i + ((y + j) * 64);

        // colision
        if (pixelArray[index] != 0) {
          registers->vx[0xF] = 1;
        }

        pixelArray[index] ^= 1;
      }
    }
  }
});

const Instruction Instruction::_Ex9E([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;
  uint8_t keyToCheck = registers->vx[index];

  if (mmu->isKeyDown(keyToCheck)) {
    registers->pc += 2;
  }
});

const Instruction Instruction::_ExA1([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;
  uint8_t keyToCheck = registers->vx[index];

  if (!mmu->isKeyDown(keyToCheck)) {
    registers->pc += 2;
  }
});

const Instruction Instruction::_Fx07([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;

  registers->vx[index] = mmu->getDelayTimer();
});

const Instruction Instruction::_Fx0A([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;
  uint8_t keyToCheck = registers->vx[index];

  if (!mmu->isKeyDown(keyToCheck)) {
    registers->pc -= 2;
  }
});

const Instruction Instruction::_Fx15([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;

  mmu->setDelayTimer(registers->vx[index]);
});

const Instruction Instruction::_Fx18([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;

  mmu->setSoundTimer(registers->vx[index]);
});

const Instruction Instruction::_Fx1E([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint16_t oldIValue = registers->I;
  uint8_t index = (opCode & 0x0F00) >> 8;

  registers->I += registers->vx[index];

  if (registers->I >= 0x1000 && oldIValue < 0x1000) {
    registers->vx[0xF] = 1;
  }
});

const Instruction Instruction::_Fx29([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;
  // 0x50 is the memory location we used for the font, 5 is the size of a font in bytes
  registers->I = 0x50 + registers->vx[index] * 5;
});

const Instruction Instruction::_Fx33([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;
  uint8_t value = registers->vx[index];

  uint8_t units = value % 10;
  uint8_t tens = ((value % 100) - units) / 10;
  uint8_t hundreds = (value - tens * 10 - units) / 100;

  mmu->setByte(registers->I, hundreds);
  mmu->setByte(registers->I + 1, tens);
  mmu->setByte(registers->I + 2, units);
});

const Instruction Instruction::_Fx55([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;

  for (int i = 0; i <= index; i++) {
    mmu->setByte(registers->I + i, registers->vx[i]);
  }
});

const Instruction Instruction::_Fx65([] (Registers* registers, MMU* mmu, uint16_t opCode) -> void {
  uint8_t index = (opCode & 0x0F00) >> 8;

  for (int i = 0; i <= index; i++) {
    registers->vx[i] = mmu->getByte(registers->I + i);
  }
});

}
