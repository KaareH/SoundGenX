#pragma once

#include <functional>
#include <SFML/Audio.hpp>

class OutStream : public sf::SoundStream {
public:
	OutStream();

	std::function<bool(float* outputData, int numSamples)> func;

private:
	virtual bool onGetData(Chunk& data);
	virtual void onSeek(sf::Time timeOffset);
};
