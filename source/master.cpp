#include "master.hpp"

Master::Master() {
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
