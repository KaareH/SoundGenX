/******************************************/
/*
  playsaw.cpp
  by Gary P. Scavone, 2006
  This program will output sawtooth waveforms
  of different frequencies on each channel.
*/
/******************************************/

#include <RtAudio.h>
#include <cmath>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>

#include "master.hpp"
#include "virtualMidiKeyboard.hpp"

typedef float MY_TYPE;
#define FORMAT RTAUDIO_FLOAT32
#define SCALE  1.0


// Platform-dependent sleep routines.
#if defined( __WINDOWS_ASIO__ ) || defined( __WINDOWS_DS__ ) || defined( __WINDOWS_WASAPI__ )
#include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variants
#include <unistd.h>
#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

Master master;

void errorCallback( RtAudioError::Type type, const std::string &errorText )
{
	// This example error handling function does exactly the same thing
	// as the embedded RtAudio::error() function.
	std::cout << "in errorCallback" << std::endl;
	if ( type == RtAudioError::WARNING )
		std::cerr << '\n' << errorText << "\n\n";
	else if ( type != RtAudioError::WARNING )
		throw( RtAudioError( errorText, type ) );
}

unsigned int channels;
RtAudio::StreamOptions options;
unsigned int frameCounter = 0;
bool checkCount = false;
unsigned int nFrames = 0;
const unsigned int callbackReturnValue = 1;

//====================================================================================================================//
int audioCallback( void *outputBuffer, void * /*inputBuffer*/, unsigned int nBufferFrames,
		 double /*streamTime*/, RtAudioStreamStatus status, void *data )
{
	extern unsigned int channels;
	MY_TYPE *buffer = (MY_TYPE *) outputBuffer;

	if ( status )
		std::cout << "Stream underflow detected!" << std::endl;

	master.onGetData(buffer, nBufferFrames, channels);

	frameCounter += nBufferFrames;
	if ( checkCount && ( frameCounter >= nFrames ) ) return callbackReturnValue;
	return 0;
}
//====================================================================================================================//

int main() {
	sf::Window window(sf::VideoMode(800, 600), "My window");

	Instrument instrument;
	master.addInstrument(instrument);

	unsigned int bufferFrames, fs, device = 0, offset = 0;

	RtAudio dac;
	if ( dac.getDeviceCount() < 1 ) {
		std::cout << "\nNo audio devices found!\n";
		exit( 1 );
	}

	channels = 2;
	fs = 44100;
	if ( nFrames > 0 ) checkCount = true;

	double *data = (double *) calloc( channels, sizeof( double ) );

	// Let RtAudio print messages to stderr.
	dac.showWarnings( true );

	// Set our stream parameters for output only.
	bufferFrames = 256;
	RtAudio::StreamParameters oParams;
	oParams.deviceId = device;
	oParams.nChannels = channels;
	oParams.firstChannel = offset;

	if ( device == 0 )
		oParams.deviceId = dac.getDefaultOutputDevice();

	//options.flags = RTAUDIO_HOG_DEVICE;
	options.flags |= RTAUDIO_SCHEDULE_REALTIME;
	options.flags |= RTAUDIO_NONINTERLEAVED;

	VirtualMidiKeyboard keyboard(&master.m_instruments.back());

	try {
		dac.openStream( &oParams, NULL, FORMAT, fs, &bufferFrames, &audioCallback, (void *)data, &options, &errorCallback );
		dac.startStream();
	}
	catch ( RtAudioError& e ) {
		e.printMessage();
		goto cleanup;
	}


	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
				keyboard.handleKeyboardInput(event);
			}


		}
	}

	try {
		// Stop the stream
		dac.stopStream();
	}
	catch ( RtAudioError& e ) {
		e.printMessage();
	}

	cleanup:
	if ( dac.isStreamOpen() ) dac.closeStream();
	free( data );

	return 0;
}