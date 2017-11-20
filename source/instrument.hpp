#pragma once

#include <SFML/System/Time.hpp>
#include <memory>
#include <unordered_map>

#include "common.hpp"
#include "noteTable.hpp"
#include "voice.hpp"

class Instrument {
public:
	Instrument();

	void getSamplesAt(float* outputData, int numSamples);
	void receiveMidi(int id, uint8_t velocity, bool hit);

private:
	void updatePhaseDelta();

	double phase = 0.0f;
	double phaseDelta;
	double sampleRate = 44100.0f;
	NoteTable noteTable;

	Voice* voices;
	unsigned int voiceCount;
	unsigned int latestVoice = 0;

	std::unordered_map<int, uint8_t> keysDown; // Never use uncontrolled heap in audio
	
};
