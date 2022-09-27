#include "lib/memory/mmu.hpp"

namespace chip8_lib {

MMU::MMU(uint8_t* rom, uint32_t romSize) {
  // copy rom content into memory (starting at 0x200)
  memcpy(this->memory + 0x200, rom, romSize);

  // clear screen
  for (size_t i = 0; i < 32 * 64; i++) {
    this->screen[i] = 0;
  }

  this->stackPointer = -1;

  // Setup font in memory - conventionally stored in [0x50 - 0x9F]
  // 0
  this->memory[0x50] = 0xF0;
  this->memory[0x51] = 0x90;
  this->memory[0x52] = 0x90;
  this->memory[0x53] = 0x90;
  this->memory[0x54] = 0xF0;
  // 1
  this->memory[0x55] = 0x20;
  this->memory[0x56] = 0x60;
  this->memory[0x57] = 0x20;
  this->memory[0x58] = 0x20;
  this->memory[0x59] = 0x70;
  // 2
  this->memory[0x5A] = 0xF0;
  this->memory[0x5B] = 0x10;
  this->memory[0x5C] = 0xF0;
  this->memory[0x5D] = 0x80;
  this->memory[0x5E] = 0xF0;
  // 3
  this->memory[0x5F] = 0xF0;
  this->memory[0x60] = 0x10;
  this->memory[0x61] = 0xF0;
  this->memory[0x62] = 0x10;
  this->memory[0x63] = 0xF0;
  // 4
  this->memory[0x64] = 0x90;
  this->memory[0x65] = 0x90;
  this->memory[0x66] = 0xF0;
  this->memory[0x67] = 0x10;
  this->memory[0x68] = 0x10;
  // 5
  this->memory[0x69] = 0xF0;
  this->memory[0x6A] = 0x80;
  this->memory[0x6B] = 0xF0;
  this->memory[0x6C] = 0x10;
  this->memory[0x6D] = 0xF0;
  // 6
  this->memory[0x6E] = 0xF0;
  this->memory[0x6F] = 0x80;
  this->memory[0x70] = 0xF0;
  this->memory[0x71] = 0x90;
  this->memory[0x72] = 0xF0;
  // 7
  this->memory[0x73] = 0xF0;
  this->memory[0x74] = 0x10;
  this->memory[0x75] = 0x20;
  this->memory[0x76] = 0x40;
  this->memory[0x77] = 0x40;
  // 8
  this->memory[0x78] = 0xF0;
  this->memory[0x79] = 0x90;
  this->memory[0x7A] = 0xF0;
  this->memory[0x7B] = 0x90;
  this->memory[0x7C] = 0xF0;
  // 9
  this->memory[0x7D] = 0xF0;
  this->memory[0x7E] = 0x90;
  this->memory[0x7F] = 0xF0;
  this->memory[0x80] = 0x10;
  this->memory[0x81] = 0xF0;
  // A
  this->memory[0x82] = 0xF0;
  this->memory[0x83] = 0x90;
  this->memory[0x84] = 0xF0;
  this->memory[0x85] = 0x90;
  this->memory[0x86] = 0x90;
  // B
  this->memory[0x87] = 0xE0;
  this->memory[0x88] = 0x90;
  this->memory[0x89] = 0xE0;
  this->memory[0x8A] = 0x90;
  this->memory[0x8B] = 0xE0;
  // C
  this->memory[0x8C] = 0xF0;
  this->memory[0x8D] = 0x80;
  this->memory[0x8E] = 0x80;
  this->memory[0x8F] = 0x80;
  this->memory[0x90] = 0xF0;
  // D
  this->memory[0x91] = 0xE0;
  this->memory[0x92] = 0x90;
  this->memory[0x93] = 0x90;
  this->memory[0x94] = 0x90;
  this->memory[0x95] = 0xE0;
  // E
  this->memory[0x96] = 0xF0;
  this->memory[0x97] = 0x80;
  this->memory[0x98] = 0xF0;
  this->memory[0x99] = 0x80;
  this->memory[0x9A] = 0xF0;
  // F
  this->memory[0x9B] = 0xF0;
  this->memory[0x9C] = 0x80;
  this->memory[0x9D] = 0xF0;
  this->memory[0x9E] = 0x80;
  this->memory[0x9F] = 0x80;
}

uint8_t MMU::getByte(uint16_t address) {
  return this->memory[address & 0x0FFF];
}

void MMU::setByte(uint16_t address, uint8_t value) {
  this->memory[address & 0x0FFF] = value;
}

uint16_t MMU::getShort(uint16_t address) {
  uint16_t maskedAddress = address & 0x0FFF;

  return this->memory[maskedAddress] << 8 | this->memory[maskedAddress + 1];
}

uint8_t* MMU::getScreen() {
  return this->screen;
}

void MMU::pushOnStack(uint16_t value) {
  if (this->stackPointer < 15) {
    this->stackPointer++;
    this->stack[this->stackPointer] = value;
  }
}

uint16_t MMU::popStack() {
  uint16_t value = 0;

  if (this->stackPointer >= 0) {
    value = this->stack[this->stackPointer];

    this->stackPointer--;
  }

  return value;
}

uint8_t MMU::getDelayTimer() {
  return this->delayTimer;
}

void MMU::setDelayTimer(uint8_t value) {
  this->delayTimer = value;
}

void MMU::decrementDelayTimer() {
  if (this->delayTimer > 0) {
    this->delayTimer--;
  }
}

uint8_t MMU::getSoundTimer() {
  return this->soundTimer;
}

void MMU::setSoundTimer(uint8_t value) {
  this->soundTimer = value;
}

void MMU::decrementSoundTimer() {
  if (this->soundTimer > 0) {
    this->soundTimer--;
  }
}

bool MMU::isKeyDown(uint8_t keyIndex) {
  return this->keyPressed[keyIndex & 0x0F];
}

void MMU::setKeyDown(uint8_t keyIndex, bool value) {
  this->keyPressed[keyIndex & 0x0F] = value;
}

}
