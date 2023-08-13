#include "GlobalSound.h"

float GlobalSound::GlobalVolume = 1.0f;
std::vector<GameEngineSoundPlayer*> GlobalSound::SoundPlayers;
std::vector<float> GlobalSound::SoundPlayersVolume;

GlobalSound::GlobalSound()
{
}

GlobalSound::~GlobalSound()
{
	size_t PlayersNum = SoundPlayers.size();
	for (size_t i = 0; i < PlayersNum; i++)
	{
		if (nullptr != SoundPlayers[i])
		{
			delete SoundPlayers[i];
		}
	}
}

GameEngineSoundPlayer* GlobalSound::CreateSoundPlayer(const std::string& FileName, int Loop, float Volume)
{
	GameEngineSoundPlayer* SoundPlayer = new GameEngineSoundPlayer;
	*SoundPlayer = GameEngineSound::SoundPlay(FileName);
	SoundPlayer->SetLoop(Loop);
	SoundPlayer->SetVolume(Volume);

	SoundPlayers.push_back(SoundPlayer);
	SoundPlayersVolume.push_back(Volume);
	return SoundPlayer;
}

void GlobalSound::AllSetVolume()
{
	size_t PlayersNum = SoundPlayers.size();
	for (size_t i = 0; i < PlayersNum; i++)
	{
		if (nullptr == SoundPlayers[i])
		{
			return;
		}
		SoundPlayers[i]->SetVolume(SoundPlayersVolume[i]);
	}
}

void GlobalSound::GlobalVolumeDown(float _Delta)
{
	GlobalVolume -= _Delta;
	if (0.0f > GlobalVolume)
	{
		GlobalVolume = 0.0f;
	}
	GameEngineSound::SetGlobalVolume(GlobalVolume);
	AllSetVolume();
}

void GlobalSound::GlobalVolumeUp(float _Delta)
{
	GlobalVolume += _Delta;
	if (3.0f < GlobalVolume)
	{
		GlobalVolume = 3.0f;
	}
	GameEngineSound::SetGlobalVolume(GlobalVolume);
	AllSetVolume();
}