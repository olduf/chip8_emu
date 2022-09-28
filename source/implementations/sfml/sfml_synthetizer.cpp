#include "implementations/sfml/sfml_synthetizer.hpp"

SFMLSynthetizer::SFMLSynthetizer() {
  const unsigned SAMPLES = 44100;
  const unsigned SAMPLE_RATE = 44100;
  const unsigned AMPLITUDE = 30000;

  sf::Int16 raw[SAMPLES];

  const double TWO_PI = 6.28318;
  const double increment = 440./44100;
  double x = 0;
  for (unsigned i = 0; i < SAMPLES; i++) {
    raw[i] = AMPLITUDE * sin(x*TWO_PI);
    x += increment;
  }

  if (this->soundBuffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
    this->sound.setBuffer(this->soundBuffer);
    this->sound.setLoop(true);
  }

  this->playing = false;
}

void SFMLSynthetizer::play() {
  if (!this->playing) {
    this->playing = true;
    this->sound.play();
  }
}
void SFMLSynthetizer::stop() {
  if (this->playing) {
    this->playing = false;
    this->sound.stop();;
  }
}
