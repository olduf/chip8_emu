#include "implementations/sfml/sfml_processor.hpp"

SFMLProcessor::SFMLProcessor() {
  this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Chip8 Emulator");
  this->inputHandler = new SFMLInputHandler();
  this->renderer = new SFMLRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SCALE);
  this->synthetizer = new SFMLSynthetizer();
}

SFMLProcessor::~SFMLProcessor() {
  if (this->inputHandler != nullptr) {
    delete this->inputHandler;
    this->inputHandler = nullptr;
  }

  if (this->renderer != nullptr) {
    delete this->renderer;
    this->renderer = nullptr;
  }

  if (this->synthetizer != nullptr) {
    delete this->synthetizer;
    this->synthetizer = nullptr;
  }

  if (this->window != nullptr) {
    delete this->window;
    this->window = nullptr;
  }
}

int SFMLProcessor::start(chip8_lib::Chip8* chip8) {
  this->clock.restart();

  while (this->window->isOpen()) {
    sf::Event event;

    while (this->window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        this->window->close();
      }

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          this->window->close();
        }
      }
    }

    this->run(chip8);

    this->window->display();
  }

  return EXIT_SUCCESS;
}

chip8_lib::InputHandler* SFMLProcessor::getInputHandler() {
  return this->inputHandler;
}

chip8_lib::Renderer* SFMLProcessor::getRenderer() {
  return this->renderer;
}
chip8_lib::Synthetizer* SFMLProcessor::getSynthetizer() {
  return this->synthetizer;
}

void SFMLProcessor::handleTiming() {
  sf::sleep(FRAME_TIME - this->clock.getElapsedTime());

  this->clock.restart();
  this->frameProcessed = false;

  this->window->clear(BACKGROUND_COLOR);
  this->window->draw(this->renderer->getSprite());
}
