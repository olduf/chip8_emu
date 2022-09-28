#pragma once

#include <cmath>
#include <SFML/Audio.hpp>
#include "lib/audio/synthetizer.hpp"

class SFMLSynthetizer : public chip8_lib::Synthetizer
{
public:
  SFMLSynthetizer();
  virtual ~SFMLSynthetizer() = default;

  void play();
  void stop();

private:
  bool playing;
  sf::Sound sound;
  sf::SoundBuffer soundBuffer;
};
