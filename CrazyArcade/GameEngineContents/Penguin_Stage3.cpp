#include <GameEngineCore/TileMap.h>

#include "Penguin_Stage3.h"
#include "FadeObject.h"
#include "Penguin.h"
#include "BaseCharacter.h"
#include "GlobalUtils.h"

Penguin_Stage3::Penguin_Stage3()
{

}

Penguin_Stage3::~Penguin_Stage3()
{

}


void Penguin_Stage3::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevel::LevelStart(_PrevLevel);
	FadeObject::CallFadeIn(this, 0.4f);

	// BGM
	BGMPlayer = GameEngineSound::SoundPlay("Boss_1_Phase_BGM.wav", 10000);
	BGMPlayer.SetVolume(BGMVolume);

	// Map
	MapFileLoad("Penguin_Stage3.map");
	TileSetting();

	// Item
	ItemSetting();

	if (Player != nullptr)
	{
		Player->SetPos(GroundTile->IndexToPos(7, 13));
	}
	else
	{
		MsgBoxAssert("1P가 생성되지 못 했습니다");
		return;
	}

	if (Player2 != nullptr)
	{
		Player2->SetPos(GroundTile->IndexToPos(9, 13));
	}

	
	if (nullptr == Penguin::BossMonster)
	{
		Penguin::BossMonster = CreateMonster<Penguin>();
	}
	Penguin::BossMonster->SetPos(GroundTile->IndexToPos(8, 6));
}

void Penguin_Stage3::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);

	if (nullptr != Penguin::BossMonster)
	{
		Penguin::BossMonster->Death();
		MonsterListDelete();
		Penguin::BossMonster = nullptr;
	}
}

void Penguin_Stage3::Start()
{
	PlayLevel::Start();

	// Sound
	GlobalUtils::SoundFileLoad("Boss_1_Phase_BGM.wav", "Resources\\Sounds\\BGM");
	GlobalUtils::SoundFileLoad("Boss_2_Phase_BGM.wav", "Resources\\Sounds\\BGM");
	BGMVolume = 1.0f;

	CurrentStage = 3;
	NextLevelName = "RoomLevel";
	CreateUIElements();
}

void Penguin_Stage3::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void Penguin_Stage3::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}