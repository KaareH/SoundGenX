#include "instrument.hpp"

#include <cmath>
#include <iostream>

Instrument::Instrument() {
	updatePhaseDelta();
}

void Instrument::getSamplesAt(float* outputData, int numSamples) {
	double tempPhase = phase;
	for(auto key : keysDown) {
		int note = key.first;
		uint8_t velocity = key.second;

		double hz = noteTable.getNoteFreq(note);
		double hz2 = hz * 2;
		double hz3 = hz2 * 2;

		phase = tempPhase;
		for(int i = 0; i < numSamples; i++) {
			float currentSample = 0.0f;
			//Organ
			currentSample += std::sin(phase * hz * 0.5) * 0.2f;
			currentSample += std::sin(phase * hz * 1) * 0.4f;
			currentSample += std::sin(phase * hz * 2) * 0.3f;
			currentSample += std::sin(phase * hz * 3) * 0.2f;
			currentSample += std::sin(phase * hz * 4) * 0.1f;

			currentSample += std::sin(phase * hz2 * 0.5) * 0.2f;
			currentSample += std::sin(phase * hz2 * 1) * 0.4f;
			currentSample += std::sin(phase * hz2 * 2) * 0.3f;
			currentSample += std::sin(phase * hz2 * 3) * 0.2f;
			currentSample += std::sin(phase * hz2 * 4) * 0.1f;

			currentSample += std::sin(phase * hz3 * 0.5) * 0.2f;
			currentSample += std::sin(phase * hz3 * 1) * 0.4f;
			currentSample += std::sin(phase * hz3 * 2) * 0.3f;
			currentSample += std::sin(phase * hz3 * 3) * 0.2f;
			currentSample += std::sin(phase * hz3 * 4) * 0.1f;

			outputData[i] += currentSample * 0.1f * (double)(velocity / 100.0f);

			phase += phaseDelta;
		}
	}
	phase = tempPhase + (phaseDelta * numSamples);
}

void Instrument::updatePhaseDelta() {
	double sampleLength = 1.0f / sampleRate;
	phaseDelta = sampleLength * PI * 2.0f;
}

void Instrument::receiveMidi(int id, uint8_t velocity, bool hit) {
	std::cout << "Midi received. Id: " << id << " Velocity: " << (int)velocity << " Hit: " << hit << std::endl;
	if(hit) {
		keysDown.insert({id, velocity});
	}
	else {
		try {
			keysDown.erase(id);
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "Keys down size: " << keysDown.size() << std::endl;
}
