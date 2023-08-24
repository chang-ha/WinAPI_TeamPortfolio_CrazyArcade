#include "Penguin_Stage2.h"
#include "FadeObject.h"
#include "BaseCharacter.h"
#include "Snowmon_black.h"
#include "Snowmon_red.h"
#include "GlobalUtils.h"
#include <GameEngineCore/TileMap.h>

Penguin_Stage2::Penguin_Stage2()
{

}

Penguin_Stage2::~Penguin_Stage2()
{

}

void Penguin_Stage2::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevel::LevelStart(_PrevLevel);
	FadeObject::CallFadeIn(this, 0.4f);

	// BGM
	BGMPlayer = GameEngineSound::SoundPlay("Penguin_Stage_BGM.wav", 10000);
	BGMPlayer.SetVolume(BGMVolume);

	// Map
	MapFileLoad("Penguin_Stage2.map");
	TileSetting();

	// Item
	ItemSetting();

	SetItemInBlock(3, 1, ItemType::Needle);
	SetItemInBlock(11, 1, ItemType::Needle);
	SetItemInBlock(3, 11, ItemType::Needle);
	SetItemInBlock(11, 11, ItemType::Needle);

	SetItemInBlock(5, 1, ItemType::Fluid);
	SetItemInBlock(9, 1, ItemType::Fluid);
	SetItemInBlock(5, 11, ItemType::Fluid);
	SetItemInBlock(9, 11, ItemType::Fluid);

	SetItemInBlock(5, 5, ItemType::Ultra);
	SetItemInBlock(9, 5, ItemType::Ultra);

	// Player
	if (Player != nullptr)
	{
		Player->SetPos(GroundTile->IndexToPos(2, 2));
	}
	else
	{
		MsgBoxAssert("1P가 생성되지 못 했습니다");
		return;
	}

	if (Player2 != nullptr)
	{
		Player2->SetPos(GroundTile->IndexToPos(14, 2));
	}

	// Snowmon Black
	Snowmon_black* Snowmon_Black = CreateMonster<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(5, 1));

	Snowmon_Black = CreateMonster<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(2, 5));

	Snowmon_Black = CreateMonster<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(2, 9));

	Snowmon_Black = CreateMonster<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(11, 1));

	Snowmon_Black = CreateMonster<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(14, 5));

	Snowmon_Black = CreateMonster<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(14, 9));

	Snowmon_Black = CreateMonster<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(5, 13));

	Snowmon_Black = CreateMonster<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(11, 13));

	// Snowmon Red
	Snowmon_red* Snowmon_Red = CreateMonster<Snowmon_red>();
	Snowmon_Red->SetPos(GroundTile->IndexToPos(7, 6));

	Snowmon_Red = CreateMonster<Snowmon_red>();
	Snowmon_Red->SetPos(GroundTile->IndexToPos(9, 6));

	Snowmon_Red = CreateMonster<Snowmon_red>();
	Snowmon_Red->SetPos(GroundTile->IndexToPos(7, 8));

	Snowmon_Red = CreateMonster<Snowmon_red>();
	Snowmon_Red->SetPos(GroundTile->IndexToPos(9, 8));
}

void Penguin_Stage2::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
}

void Penguin_Stage2::Start()
{
	PlayLevel::Start();

	// Sound
	GlobalUtils::SoundFileLoad("Penguin_Stage_BGM.wav", "Resources\\Sounds\\BGM");
	BGMVolume = 1.0f;

	CurrentStage = 2;
	NextLevelName = "Penguin_Stage3";
	CreateUIElements();
}

void Penguin_Stage2::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void Penguin_Stage2::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}