#pragma once

#include <vector>

#include "instrument.hpp"

class Master {
public:
	Master();

	bool onGetData(float* outputData, int numSamples);
	void addInstrument(Instrument& instrument);

private:
	std::vector<Instrument> m_instruments;
};
