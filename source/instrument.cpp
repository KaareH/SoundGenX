#include "instrument.hpp"

#include <cmath>
#include <iostream>

Instrument::Instrument() {
	updatePhaseDelta();
	voiceCount = 5;
	voices = new Voice[voiceCount];
}

void Instrument::getSamplesAt(float* outputData, int numSamples) {
	double tempPhase = phase;
	for(int vi = 0; vi < voiceCount; vi++) {
		Voice* voice = &voices[vi];
		uint8_t velocity = voice->velocity;

		double hz = voice->pitch;
		double hz2 = hz * 2;
		double hz3 = hz * 4;

		phase = tempPhase;
		for(int i = 0; i < numSamples; i++) {
			float currentSample = 0.0f;
			//Organ
			currentSample += std::sin(phase * hz * 0.5) * 0.2f;
			currentSample += std::sin(phase * hz * 1) * 0.4f;
			currentSample += std::sin(phase * hz * 2) * 0.3f;
			currentSample += std::sin(phase * hz * 3) * 0.2f;
			currentSample += std::sin(phase * hz * 4) * 0.1f;

			currentSample += std::sin(phase * hz2 * 0.5) * 0.2f;
			currentSample += std::sin(phase * hz2 * 1) * 0.4f;
			currentSample += std::sin(phase * hz2 * 2) * 0.3f;
			currentSample += std::sin(phase * hz2 * 3) * 0.2f;
			currentSample += std::sin(phase * hz2 * 4) * 0.1f;

			currentSample += std::sin(phase * hz3 * 0.5) * 0.2f;
			currentSample += std::sin(phase * hz3 * 1) * 0.4f;
			currentSample += std::sin(phase * hz3 * 2) * 0.3f;
			currentSample += std::sin(phase * hz3 * 3) * 0.2f;
			currentSample += std::sin(phase * hz3 * 4) * 0.1f;

			/*currentSample += std::sin(phase * hz * 1) * 0.4f;
			currentSample += std::sin(phase * hz2 * 1) * 0.4f;
			currentSample += std::sin(phase * hz3 * 1) * 0.4f;*/
			//currentSample += std::sin(phase * hz * 0.5) * sin(phase * 300) * 0.4f;
			//currentSample += std::sin(phase * hz * std::tan(phase )) * 0.5f;
			//currentSample += std::sin(phase * hz + 5 * sin(phase * hz / 80)) * 0.4f;

			outputData[i] += currentSample * 0.1f * (double)(velocity / 100.0f) * voice->decay;
			voice->decay -= 0.00001;
			if(voice->decay < 0) {
				voice->decay = 0;
			}
			phase += phaseDelta;
		}
	}
	phase = tempPhase + (phaseDelta * numSamples);
}

void Instrument::updatePhaseDelta() {
	double sampleLength = 1.0f / sampleRate;
	phaseDelta = sampleLength * PI * 2.0f;
}

void Instrument::receiveMidi(int id, uint8_t velocity, bool hit) {
	std::cout << "Midi received. Id: " << id << " Velocity: " << (int)velocity << " Hit: " << hit << std::endl;
	if(hit) {
		Voice* voice = &voices[latestVoice];
		latestVoice++;
		if(latestVoice >= voiceCount) {
			latestVoice = 0;
		}

		voice->pitch = noteTable.getNoteFreq(id);
		voice->velocity = velocity;
		voice->decay = 1;
	}
	/*
	if(hit) {
		keysDown.insert({id, velocity});
	}
	else {
		try {
			keysDown.erase(id);
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}
	}*/
	std::cout << "Keys down size: " << keysDown.size() << std::endl;
}
