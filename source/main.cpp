#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <iostream>

#include "master.hpp"

int main() {
	Master master;
	Instrument instrument;
	master.addInstrument(instrument);

	while (true)
		sf::sleep(sf::seconds(0.1f));

	return 0;
}
