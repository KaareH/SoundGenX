#pragma once

#include <SFML/System/Time.hpp>

#include "common.hpp"

class Instrument {
public:
	Instrument();

	void getSamplesAt(float* outputData, int numSamples);

private:
	void updatePhaseDelta();

	double phase = 0.0f;
	double phaseDelta;
	double sampleRate = 44100.0f;
};
