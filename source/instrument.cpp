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
		//currentSample += std::sin(phase * hz * 0.5) * 0.2f;//5000;
		currentSample += std::sin(phase * hz * 1) * 0.4f;//10000;
		/*currentSample += std::sin(phase * hz * 2) * 0.3f;//7000;
		currentSample += std::sin(phase * hz * 3) * 0.2f;//5000;
		currentSample += std::sin(phase * hz * 4) * 0.1f;//3000;*/

		/*currentSample += std::sin(phase * hz2 * 0.5) * 5000;
		currentSample += std::sin(phase * hz2 * 1) * 10000;
		currentSample += std::sin(phase * hz2 * 2) * 7000;
		currentSample += std::sin(phase * hz2 * 3) * 5000;
		currentSample += std::sin(phase * hz2 * 4) * 3000;

		currentSample += std::sin(phase * hz3 * 0.5) * 5000;
		currentSample += std::sin(phase * hz3 * 1) * 10000;
		currentSample += std::sin(phase * hz3 * 2) * 7000;
		currentSample += std::sin(phase * hz3 * 3) * 5000;
		currentSample += std::sin(phase * hz3 * 4) * 3000;*/

		outputData[i] = currentSample;

		phase += phaseDelta;
	}
}

void Instrument::updatePhaseDelta() {
	float sampleLength = 1.0f / sampleRate;
	phaseDelta = sampleLength * PI * 2.0f;
}
