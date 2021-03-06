#include "Sound.h"
#include "GameGlobal.h"

Sound* Sound::instance = nullptr;

Sound* Sound::getInstance()
{
	if (instance == nullptr)
		instance = new Sound(GameGlobal::getCurrentHWND());

	return instance;
}

Sound::Sound(HWND hWnd)
{
	primaryBuffer = nullptr;

	DSBUFFERDESC bufferDesc; //describe the buffer

	HRESULT result = DirectSoundCreate8(nullptr, &pDevice, nullptr);

	if (FAILED(result))
		return;

	pDevice->SetCooperativeLevel(hWnd, DSSCL_PRIORITY); // set the cooperative level.

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = nullptr;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = pDevice->CreateSoundBuffer(&bufferDesc, &primaryBuffer, nullptr);

	if (FAILED(result))
		return;
	volume = 100.0f;
	isMute = false;
}

Sound::~Sound()
{
	for (auto it = soundBufferMap.begin(); it != soundBufferMap.end(); ++it)
	{
		if (it->second)
		{
			it->second->Release();
			it->second = nullptr;
		}
	}
	if (primaryBuffer)
		primaryBuffer->Release();
	if (pDevice)
		pDevice->Release();
	pDevice = nullptr;

	primaryBuffer = nullptr;
}

void Sound::create(HWND hWnd)
{
	if (instance == nullptr)
	{
		instance = new Sound(hWnd);
	}
}

float Sound::getVolume() const
{
	return volume;
}

void Sound::loadSound(char* fileName, const std::string& name)
{
	if (soundBufferMap.find(name) != soundBufferMap.end())
		return;
	FILE* filePtr;
	WaveHeaderStruct waveHeaderStruct;
	IDirectSoundBuffer* tempBuffer;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

	int error = fopen_s(&filePtr, fileName, "rb");
	if (error != 0)
		return;

	fread(&waveHeaderStruct, sizeof(WaveHeaderStruct), 1, filePtr);
	//fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);

	if ((waveHeaderStruct.format[0] != 'W') || (waveHeaderStruct.format[1] != 'A') ||
		(waveHeaderStruct.format[2] != 'V') || (waveHeaderStruct.format[3] != 'E'))
		return;

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = waveHeaderStruct.sampleRate;
	waveFormat.wBitsPerSample = waveHeaderStruct.bitsPerSample;
	waveFormat.nChannels = waveHeaderStruct.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = waveHeaderStruct.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer8* secondaryBuffer = nullptr;
	IDirectSoundBuffer8** pSecondaryBuffer = &secondaryBuffer;
	//IDirectSoundBuffer8

	//long result = pDevice->CreateSoundBuffer(&bufferDesc, &secondaryBuffer, NULL);

	pDevice->CreateSoundBuffer(&bufferDesc, &tempBuffer, nullptr);

	long result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, reinterpret_cast<void**>(&(*pSecondaryBuffer)));

	tempBuffer->Release();
	tempBuffer = nullptr;

	if (FAILED(result))
		return;

	//fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET); // move the filePointer cursor to data section

	fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET);


	auto* wavData = new unsigned char[ waveHeaderStruct.dataSize];


	fread(wavData, waveHeaderStruct.dataSize, 1, filePtr);

	error = fclose(filePtr);
	if (error != 0)
		return;

	result = (*pSecondaryBuffer)->Lock(0, waveHeaderStruct.dataSize, reinterpret_cast<void**>(&bufferPtr), static_cast<DWORD*>(&bufferSize), nullptr, nullptr, 0);

	if (FAILED(result))
		return;

	memcpy(bufferPtr, wavData, waveHeaderStruct.dataSize);

	(*pSecondaryBuffer)->Unlock(static_cast<void*>(bufferPtr), bufferSize, nullptr, 0);

	if (wavData != nullptr)
	{
		delete[] wavData;
		wavData = nullptr;
	}

	long tempVolume = (volume) / 100 * (- DSBVOLUME_MIN) + DSBVOLUME_MIN;
	(*pSecondaryBuffer)->SetVolume(tempVolume);

	soundBufferMap[name] = secondaryBuffer;
}

void Sound::play(const std::string& name, bool infiniteLoop, int times)
{
	if (isMute)
		return;

	auto it = soundBufferMap.find(name);
	if (it == soundBufferMap.end())
		return;
	if (infiniteLoop)
	{
		it->second->Play(0, 0, DSBPLAY_LOOPING);
	}
	else
	{
		it->second->Stop();
		it->second->SetCurrentPosition(0);
		it->second->Play(0, 0, times - 1);
	}
}

void Sound::stop(const std::string& name)
{
	if (name.empty())
	{
		for (auto it = soundBufferMap.begin(); it != soundBufferMap.
		     end(); ++it)
		{
			it->second->Stop();
			it->second->SetCurrentPosition(0);
		}
	}
	else
	{
		auto it = soundBufferMap.find(name);
		if (it == soundBufferMap.end())
			return;
		it->second->Stop();
	}
}

void Sound::setVolume(float percentage, const std::string& name)
{
	volume = percentage;
	if (name.empty())
	{
		long volume = (percentage) / 100 * (- DSBVOLUME_MIN) + DSBVOLUME_MIN;
		for (auto it = soundBufferMap.begin(); it != soundBufferMap.end(); ++it)
		{
			it->second->SetVolume(volume);
		}
	}
	else
	{
		auto it = soundBufferMap.find(name);
		if (it == soundBufferMap.end())
			return;
		long volume = (percentage) / 100 * (- DSBVOLUME_MIN) + DSBVOLUME_MIN;
		it->second->SetVolume(volume);
	}
}

void Sound::mute()
{
	isMute = true;
	getInstance()->stop();
}

void Sound::unMute()
{
	isMute = false;
}

void Sound::cleanUp() const
{
	delete this;
}
