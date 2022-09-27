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
}

void SFMLSynthetizer::play() {
  this->sound.play();
}
void SFMLSynthetizer::stop() {
  this->sound.stop();
}
