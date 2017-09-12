#include "instrument.hpp"

#include <cmath>
#include <iostream>

Instrument::Instrument() {
	updatePhaseDelta();
}

void Instrument::getSamplesAt(float* outputData, int numSamples) {
	double hz = 440;
	double hz2 = 880;
	double hz3 = 1760;

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

		outputData[i] = currentSample * 0.5;

		phase += phaseDelta;
	}
}

void Instrument::updatePhaseDelta() {
	double sampleLength = 1.0f / sampleRate;
	phaseDelta = sampleLength * PI * 2.0f;
}
