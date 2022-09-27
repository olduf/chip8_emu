#pragma once

#include <cstdint>
#include <cstring>

namespace chip8_lib {

class MMU
{
public:
  MMU(uint8_t* rom, uint32_t romSize);

  uint8_t getByte(uint16_t address);
  void setByte(uint16_t address, uint8_t value);

  uint16_t getShort(uint16_t address);
  uint8_t* getScreen();

  void pushOnStack(uint16_t value);
  uint16_t popStack();

  uint8_t getDelayTimer();
  void setDelayTimer(uint8_t value);
  void decrementDelayTimer();

  uint8_t getSoundTimer();
  void setSoundTimer(uint8_t value);
  void decrementSoundTimer();

  bool isKeyDown(uint8_t keyIndex);
  void setKeyDown(uint8_t keyIndex, bool value);

private:
  bool keyPressed[16];

  uint8_t memory[4096];
  uint8_t screen[32*64];

  uint8_t delayTimer;
  uint8_t soundTimer;

  uint16_t stack[16];
  int stackPointer;
};

}
