#include "lib/cpu/cpu.hpp"

namespace chip8_lib {

Cpu::Cpu(MMU* mmu) {
  this->mmu = mmu;
}

void Cpu::tick() {
  uint16_t opCode = this->mmu->getShort(this->registers.pc);

  this->registers.pc += 2;

  switch (opCode & 0xF000) {
    case 0: {
      switch (opCode & 0x00FF) {
        case 0xE0:
          Instruction::_00E0.execute(&this->registers, this->mmu, opCode);
          break;
        case 0xEE:
          Instruction::_00EE.execute(&this->registers, this->mmu, opCode);
          break;
      }

      break;
    }
    // JP addr
    case 0x1000:
      Instruction::_1nnn.execute(&this->registers, this->mmu, opCode);
      break;
    // CALL addr
    case 0x2000:
      Instruction::_2nnn.execute(&this->registers, this->mmu, opCode);
      break;
    // SE Vx, byte
    case 0x3000:
      Instruction::_3xnn.execute(&this->registers, this->mmu, opCode);
      break;
    // SNE Vx, byte
    case 0x4000:
      Instruction::_4xnn.execute(&this->registers, this->mmu, opCode);
      break;
    // SE Vx, Vy
    case 0x5000:
      Instruction::_5xy0.execute(&this->registers, this->mmu, opCode);
      break;
    // LD Vx, byte
    case 0x6000:
      Instruction::_6xnn.execute(&this->registers, this->mmu, opCode);
      break;
    // ADD Vx, byte
    case 0x7000:
      Instruction::_7xnn.execute(&this->registers, this->mmu, opCode);
      break;
    // Logical and arithmetic instructions
    case 0x8000: {
      switch (opCode & 0x000F) {
        case 0:
          Instruction::_8xy0.execute(&this->registers, this->mmu, opCode);
          break;
        case 1:
          Instruction::_8xy1.execute(&this->registers, this->mmu, opCode);
          break;
        case 2:
          Instruction::_8xy2.execute(&this->registers, this->mmu, opCode);
          break;
        case 3:
          Instruction::_8xy3.execute(&this->registers, this->mmu, opCode);
          break;
        case 4:
          Instruction::_8xy4.execute(&this->registers, this->mmu, opCode);
          break;
        case 5:
          Instruction::_8xy5.execute(&this->registers, this->mmu, opCode);
          break;
        case 6:
          Instruction::_8xy6.execute(&this->registers, this->mmu, opCode);
          break;
        case 7:
          Instruction::_8xy7.execute(&this->registers, this->mmu, opCode);
          break;
        case 0xE:
          Instruction::_8xyE.execute(&this->registers, this->mmu, opCode);
          break;
      }

      break;
    }
    // SNE Vx, Vy
    case 0x9000:
      Instruction::_9xy0.execute(&this->registers, this->mmu, opCode);
      break;
    // LD I, addr
    case 0xA000:
      Instruction::_Annn.execute(&this->registers, this->mmu, opCode);
      break;
    // JP V0, addr
    case 0xB000:
      Instruction::_Bnnn.execute(&this->registers, this->mmu, opCode);
      break;
    // RND Vx, byte
    case 0xC000:
      Instruction::_Cxnn.execute(&this->registers, this->mmu, opCode);
      break;
    // DRW Vx, Vy, nibble
    case 0xD000:
      Instruction::_Dxyn.execute(&this->registers, this->mmu, opCode);
      break;
    case 0xE000: {
      switch (opCode & 0x00FF) {
        case 0x9E:
          Instruction::_Ex9E.execute(&this->registers, this->mmu, opCode);
          break;
        case 0xA1:
          Instruction::_ExA1.execute(&this->registers, this->mmu, opCode);
          break;
      }

      break;
    }
    case 0xF000: {
      switch (opCode & 0x0FF) {
        // LD Vx, DT
        case 0x07:
          Instruction::_Fx07.execute(&this->registers, this->mmu, opCode);
          break;
        // LD Vx, K -> Get key (blocking)
        case 0x0A:
          Instruction::_Fx0A.execute(&this->registers, this->mmu, opCode);
          break;
        // LD DT, Vx
        case 0x15:
          Instruction::_Fx15.execute(&this->registers, this->mmu, opCode);
          break;
        // LD ST, Vx
        case 0x18:
          Instruction::_Fx18.execute(&this->registers, this->mmu, opCode);
          break;
        // ADD I, Vx
        case 0x1E:
          Instruction::_Fx1E.execute(&this->registers, this->mmu, opCode);
          break;
        // LD F, Vx
        case 0x29:
          Instruction::_Fx29.execute(&this->registers, this->mmu, opCode);
          break;
        // LD B, Vx
        case 0x33:
          Instruction::_Fx33.execute(&this->registers, this->mmu, opCode);
          break;
        // LD [I], Vx
        case 0x55:
          Instruction::_Fx55.execute(&this->registers, this->mmu, opCode);
          break;
        // LD Vx, [I]
        case 0x65:
          Instruction::_Fx65.execute(&this->registers, this->mmu, opCode);
          break;
      }

      break;
    }
  }
}

}
