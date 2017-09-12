#include "master.hpp"

Master::Master() {
}

bool Master::onGetData(float* outputData, unsigned int numSamples, unsigned int channels) {

	for(auto &instrument : m_instruments) {
		float data[numSamples];
		instrument.getSamplesAt(data, numSamples);
		for(int i = 0; i < numSamples; i++) {
			for(int ch = 0; ch < channels; ch++) {
				outputData[i + numSamples * ch] = data[i];
			}
		}
	}

	return true;
}

void Master::addInstrument(Instrument &instrument) {
	m_instruments.push_back(instrument);
}
