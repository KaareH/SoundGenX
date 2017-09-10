#pragma once

#include <SFML/System/Time.hpp>

#include "common.hpp"

class Instrument {
public:
	Instrument();

	void getSamplesAt(float* outputData, int numSamples);

private:
	void updatePhaseDelta();

	float phase = 0.0f;
	float phaseDelta;
	float sampleRate = 44100.0f;
};
