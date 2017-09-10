#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>

#include "outStream.hpp"
#include "instrument.hpp"

class Master {
public:
	Master();

	bool onGetData(float* outputData, int numSamples);
	void addInstrument(Instrument& instrument);

private:
	OutStream m_outStream;
	std::vector<Instrument> m_instruments;
};
