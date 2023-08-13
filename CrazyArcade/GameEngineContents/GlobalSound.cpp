#include "GlobalSound.h"

float GlobalSound::GlobalVolume = 1.0f;
std::vector<GlobalSound*> GlobalSound::AllSoundPlayer;

GlobalSound::GlobalSound()
{
}

GlobalSound::~GlobalSound()
{
}

void GlobalSound::CreateSoundPlayer(const std::string& _FileName, int _Loop, float _Volume)
{
	SoundPlayer = GameEngineSound::SoundPlay(_FileName, _Loop);
	SoundPlayer.SetVolume(_Volume);

	AllSoundPlayer.push_back(this);
	Volume = _Volume;
}

void GlobalSound::AllSetVolume()
{
	size_t PlayersNum = AllSoundPlayer.size();
	for (size_t i = 0; i < PlayersNum; i++)
	{
		AllSoundPlayer[i]->SoundPlayer.SetVolume(AllSoundPlayer[i]->Volume);
	}
}

void GlobalSound::GlobalVolumeDown()
{
	GlobalVolume -= 0.2f;
	if (0.0f > GlobalVolume)
	{
		GlobalVolume = 0.0f;
	}
	GameEngineSound::SetGlobalVolume(GlobalVolume);
	AllSetVolume();
}

void GlobalSound::GlobalVolumeUp()
{
	GlobalVolume += 0.2f;
	if (2.0f < GlobalVolume)
	{
		GlobalVolume = 2.0f;
	}
	GameEngineSound::SetGlobalVolume(GlobalVolume);
	AllSetVolume();
}