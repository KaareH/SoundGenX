#include "outStream.hpp"

#include <iostream>

OutStream::OutStream() {
	initialize(1, 44100);
}

bool OutStream::onGetData(Chunk& data) {
	int numSamples = 512;
	float outputData[numSamples];

	bool returnValue = func(outputData, numSamples);

	data.sampleCount = numSamples;
	int16_t tempData[numSamples];
	for(int i = 0; i < numSamples; i++) {
		tempData[i] = outputData[i] * 32768; // Convert float in range -1,+1 to short range -32768,+32767
	}
	data.samples = tempData;

	return returnValue;
}

void OutStream::onSeek(sf::Time timeOffset) {
	std::cout << timeOffset.asMicroseconds() << std::endl;
}
