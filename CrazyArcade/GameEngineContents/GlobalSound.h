#pragma once
#include <GameEnginePlatform/GameEngineSound.h>
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

	static GameEngineSoundPlayer* CreateSoundPlayer(const std::string& FileName, int Loop, float Volume);
	static void AllSetVolume();
	static void GlobalVolumeDown(float _Delta);
	static void GlobalVolumeUp(float _Delta);
protected:

private:
	static float GlobalVolume;
	static std::vector<GameEngineSoundPlayer*> SoundPlayers;
	static std::vector<float> SoundPlayersVolume;
};