#include <SFML/Graphics.hpp>
#include <cxxopts.hpp>
#include <string>

#include "implementations/sfml/sfml_processor.hpp"
#include "lib/chip8.hpp"

chip8_lib::Chip8* chip8;
SFMLProcessor* processor;

void cleanup();

int main(int argc, char** argv) {
  cxxopts::Options options(argv[0], "Chip8 emulator");

  std::string romPath;

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("p,path", "Path to the rom", cxxopts::value(romPath));
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;

    return 0;
  }

  int status = 0;

  if (!romPath.empty()) {
    chip8 = new chip8_lib::Chip8(romPath);
    processor = new SFMLProcessor();
    status = processor->start(chip8);
  }

  cleanup();

  return status;
}

void cleanup() {
  if (processor != nullptr) {
    delete processor;
    processor = nullptr;
  }

  if (chip8 != nullptr) {
    delete chip8;
    chip8 = nullptr;
  }
}
