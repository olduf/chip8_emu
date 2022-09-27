#include "implementations/console/console_renderer.hpp"

void ConsoleRenderer::render(uint8_t* pixelArray) {
  // clear screen
  system("clear");

  for (int j = 0; j < 32; j++) {
    for (int i = 0; i < 64; i++) {
       pixelArray[j * 64 + i] == 0 ? std::cout << "  " : std::cout << "██";
    }

    std::cout << std::endl;
  }
}
