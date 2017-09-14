#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "instrument.hpp"

class VirtualMidiKeyboard {
public:
	VirtualMidiKeyboard(Instrument* instrument1);

	void handleKeyboardInput(sf::Event e);

private:
	int octave = 4;
	uint8_t velocity = 100;
	Instrument* instrument;

	const sf::Keyboard::Key keyMap[15] = {
			sf::Keyboard::A,
			sf::Keyboard::W,
			sf::Keyboard::S,
			sf::Keyboard::E,
			sf::Keyboard::D,
			sf::Keyboard::F,
			sf::Keyboard::T,
			sf::Keyboard::G,
			sf::Keyboard::Y,
			sf::Keyboard::H,
			sf::Keyboard::U,
			sf::Keyboard::J,
			sf::Keyboard::K,
			sf::Keyboard::O,
			sf::Keyboard::L
	};
};
