cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(chip8_emuStandalone LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME cxxopts
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.0
  OPTIONS "CXXOPTS_BUILD_EXAMPLES Off" "CXXOPTS_BUILD_TESTS Off"
)

CPMAddPackage(NAME chip8_emu SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(chip8_emuStandalone ${sources})

set_target_properties(chip8_emuStandalone PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "chip8_emu")

target_link_libraries(chip8_emuStandalone chip8_emu cxxopts)
