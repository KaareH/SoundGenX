#include "virtualMidiKeyboard.hpp"

VirtualMidiKeyboard::VirtualMidiKeyboard(Instrument* instrument1) {
instrument = instrument1;
}

void VirtualMidiKeyboard::handleKeyboardInput(sf::Event e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Z) {
			octave--;
		} else if (e.key.code == sf::Keyboard::X) {
			octave++;
		} else if (e.key.code == sf::Keyboard::C) {
			velocity -= 10;
		} else if (e.key.code == sf::Keyboard::V) {
			velocity += 10;
		} else {
			for (int i = 0; i < 15; i++) {
				if (e.key.code == keyMap[i]) {
					instrument->receiveMidi(i + octave * 12, velocity, true);
					break;
				}
			}
		}
	}
	if (e.type == sf::Event::KeyReleased) {
		for (int i = 0; i < 15; i++) {
			if (e.key.code == keyMap[i]) {
				instrument->receiveMidi(i + octave * 12, velocity, false);
				break;
			}
		}
	}
}
