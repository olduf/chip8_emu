# Chip8 Emulator
Chip8 emulator built in C++ (I am not a professional C++ dev.). Uses SFML.

Pretty sure it's buggy, but it passes the test roms, and runs space invaders and tetris.

## Requirement
 - [SFML 2.5](https://www.sfml-dev.org/index.php)
 - CMake 3.14
 - C++17 compiler

## Building the project
In a terminal, navigate to the project folder.

### Application
- Run `cmake -Hstandalone -Bbuild/standalone`
- Run `cmake --build build/standalone/`

## Usage
### Application
`./build/standalone/chip8_emu --path <path to the rom>`

#### Options
- -h, --help: show help
- -p, --path: path to the rom you want to load

## Included ROMs
### Games
- `INVADERS`
- `TETRIS`
### Test ROMs
- `BC_test.ch8` (BestCoder)
- `chip8-test-rom.ch8` (Sergey Naydenov)
- `c8_test.c8 `(Skosulor)
- `test_opcode.ch8` (corax89)

## Technical References
- [Guide to making a CHIP-8 emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)
- [Cowgod's Chip-8 Technical Reference v1.0](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
