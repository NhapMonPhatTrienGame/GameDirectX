#pragma once
#include "dsound.h"
#include "windows.h"
#include <map>
#include <string>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

class Sound
{
public:
	struct WaveHeaderStruct
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
	float volume;
	void static create(HWND hWnd);
	void setVolume(float percentage, const std::string& name = "");
	void loadSound(char* fileName, const std::string& name);
	void play(const std:: string& name , bool infiniteLoop, int times);
	void stop(const std::string& name = "");
	float getVolume() const;
	~Sound();
	static Sound* getInstance();
	void mute();
	void unMute();
	void cleanUp() const;
private:
	explicit Sound(HWND hWnd);
	static Sound * instance;
	IDirectSound8* pDevice;
	IDirectSoundBuffer* primaryBuffer;
	std::map<std::string, IDirectSoundBuffer8*> soundBufferMap;
	bool isMute;
	
};

