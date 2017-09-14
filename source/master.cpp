#include "master.hpp"

Master::Master() {
}

void Master::onGetData(float* outputData, unsigned int numSamples, unsigned int channels) {
	for(auto &instrument : m_instruments) {
		float data[numSamples];
		for(int i = 0; i < numSamples; i++) {
			data[i] = 0; // Make sure to initialize the whole array to 0, or horrible noise will occur
		}

		instrument.getSamplesAt(data, numSamples);
		for(int ch = 0; ch < channels; ch++) {
			for (int i = 0; i < numSamples; i++) {
				outputData[i + (numSamples * ch)] = data[i];
			}
		}
	}
}

void Master::addInstrument(Instrument &instrument) {
	m_instruments.push_back(instrument);
}
