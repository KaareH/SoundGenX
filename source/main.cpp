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
#include "noteTable.hpp"
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

void usage( void ) {
	// Error function in case of incorrect command-line
	// argument specifications
	std::cout << "\nuseage: playsaw N fs <device> <channelOffset> <time>\n";
	std::cout << "    where N = number of channels,\n";
	std::cout << "    fs = the sample rate,\n";
	std::cout << "    device = optional device to use (default = 0),\n";
	std::cout << "    channelOffset = an optional channel offset on the device (default = 0),\n";
	std::cout << "    and time = an optional time duration in seconds (default = no limit).\n\n";
	exit( 0 );
}

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

int main( int argc, char *argv[] ) {
	sf::Window window(sf::VideoMode(800, 600), "My window");


	NoteTable noteTable;
	Instrument instrument;
	master.addInstrument(instrument);

	unsigned int bufferFrames, fs, device = 0, offset = 0;

	// minimal command-line checking
	if (argc < 3 || argc > 6 ) usage();

	RtAudio dac;
	if ( dac.getDeviceCount() < 1 ) {
		std::cout << "\nNo audio devices found!\n";
		exit( 1 );
	}

	channels = (unsigned int) atoi( argv[1] );
	fs = (unsigned int) atoi( argv[2] );
	if ( argc > 3 )
		device = (unsigned int) atoi( argv[3] );
	if ( argc > 4 )
		offset = (unsigned int) atoi( argv[4] );
	if ( argc > 5 )
		nFrames = (unsigned int) (fs * atof( argv[5] ));
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