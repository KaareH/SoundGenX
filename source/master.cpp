#include "master.hpp"

#include <cmath>
#include <cassert>

Master::Master() {
	std::function<bool(float* outputData, int numSamples)> function = [this](float* outputData, int numSamples) {
		return onGetData(outputData, numSamples);
	};

	m_outStream.func = function;
	m_outStream.play();
}

bool Master::onGetData(float* outputData, int numSamples) {
	double sampleRate = 44100;
	for(auto &instrument : m_instruments) {
		float data[numSamples];
		instrument.getSamplesAt(data, numSamples);
		for(int i = 0; i < numSamples; i++) {
			outputData[i] = data[i];
		}
	}

	return true;
}

void Master::addInstrument(Instrument &instrument) {
	m_instruments.push_back(instrument);
}
