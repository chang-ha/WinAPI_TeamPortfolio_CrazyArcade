#pragma once
#include <GameEnginePlatform/GameEngineSound.h>

#include <vector>
class GlobalSound
{
public:
	// Constructor Destructor
	GlobalSound();
	~GlobalSound();

	// Delete Function
	GlobalSound(const GlobalSound& _Other) = delete;
	GlobalSound(GlobalSound&& _Other) noexcept = delete;
	GlobalSound& operator=(const GlobalSound& _Other) = delete;
	GlobalSound& operator=(GlobalSound&& _Other) noexcept = delete;

	void CreateSoundPlayer(const std::string& _FileName, int _Loop, float _Volume);

	inline void Stop()
	{
		SoundPlayer.Stop();
	}

	inline void SetVolume(float _Volume)
	{
		Volume = _Volume;
		SoundPlayer.SetVolume(Volume);
	}

	static void GlobalVolumeDown();
	static void GlobalVolumeUp();
	
protected:

private:
	static void AllSetVolume();

	static float GlobalVolume;
	static std::vector<GlobalSound*> AllSoundPlayer;
	
	GameEngineSoundPlayer SoundPlayer;
	float Volume = 1.0f;
};