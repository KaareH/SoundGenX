#pragma once

#include <vector>

#include "instrument.hpp"

#define SAMPLE_RATE 44100.0f

class Master {
public:
	Master();

	bool onGetData(float* outputData, unsigned int numSamples, unsigned int channels);
	void addInstrument(Instrument& instrument);

private:
	std::vector<Instrument> m_instruments;
};
