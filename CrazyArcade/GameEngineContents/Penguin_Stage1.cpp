#include "Penguin_Stage1.h"
#include "FadeObject.h"
#include "BaseCharacter.h"
#include "Snowmon_black.h"
#include "Piratemon_black.h"
#include "Piratemon_red.h"
#include "GlobalUtils.h"
#include <GameEngineCore/TileMap.h>

Penguin_Stage1::Penguin_Stage1()
{

}

Penguin_Stage1::~Penguin_Stage1()
{

}

void Penguin_Stage1::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevel::LevelStart(_PrevLevel);
	FadeObject::CallFadeIn(this, 0.4f);

	// BGM
	BGMPlayer = GameEngineSound::SoundPlay("Penguin_Stage_BGM.wav", 10000);
	BGMPlayer.SetVolume(BGMVolume);

	// Map
	MapFileLoad("Penguin_Stage1.map");
	TileSetting();

	// Item
	ItemSetting();
	SetItemInBlock(0, 6, ItemType::Needle);
	SetItemInBlock(14, 6, ItemType::Needle);

	if (Player != nullptr)
	{
		Player->SetPos(GroundTile->IndexToPos(6, 4));
	}
	else
	{
		MsgBoxAssert("1P가 생성되지 못 했습니다");
		return;
	}

	if (Player2 != nullptr)
	{
		Player2->SetPos(GroundTile->IndexToPos(6, 10));
	}

	// 오 아 왼 오 위 왼 위 오 왼 아 오 아
	std::list<ActorDir> MonsterDir;
	MonsterDir.push_back(ActorDir::Right);
	MonsterDir.push_back(ActorDir::Down);
	MonsterDir.push_back(ActorDir::Left);
	MonsterDir.push_back(ActorDir::Right);
	MonsterDir.push_back(ActorDir::Up);
	MonsterDir.push_back(ActorDir::Left);
	MonsterDir.push_back(ActorDir::Up);
	MonsterDir.push_back(ActorDir::Right);
	MonsterDir.push_back(ActorDir::Left);
	MonsterDir.push_back(ActorDir::Down);
	MonsterDir.push_back(ActorDir::Right);
	MonsterDir.push_back(ActorDir::Down);
	
	BaseMonster* Monster = CreateMonster<Snowmon_black>();
	Monster->SetPos(GroundTile->IndexToPos(1, 6));

	Monster = CreateMonster<Snowmon_black>();
	Monster->SetPos(GroundTile->IndexToPos(15, 6));

	Monster = CreateMonster<Snowmon_black>();
	Monster->SetPos(GroundTile->IndexToPos(1, 8));

	Monster = CreateMonster<Snowmon_black>();
	Monster->SetPos(GroundTile->IndexToPos(15, 8));

	Monster = CreateMonster<Piratemon_black>();
	Monster->SetPos(GroundTile->IndexToPos(6, 7));
	Monster->SetMonsterMovePattern(MonsterDir);

	Monster = CreateMonster<Piratemon_black>();
	Monster->SetPos(GroundTile->IndexToPos(7, 7));
	Monster->SetMonsterMovePattern(MonsterDir);

	Monster = CreateMonster<Piratemon_red>();
	Monster->SetPos(GroundTile->IndexToPos(8, 7));
	Monster->SetMonsterMovePattern(MonsterDir);

	Monster = CreateMonster<Piratemon_red>();
	Monster->SetPos(GroundTile->IndexToPos(9, 7));
	Monster->SetMonsterMovePattern(MonsterDir);

	Monster = CreateMonster<Piratemon_red>();
	Monster->SetPos(GroundTile->IndexToPos(10, 7));
	Monster->SetMonsterMovePattern(MonsterDir);

	Monster = CreateMonster<Piratemon_red>();
	Monster->SetPos(GroundTile->IndexToPos(11, 7));
	Monster->SetMonsterMovePattern(MonsterDir);
}

void Penguin_Stage1::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
}

void Penguin_Stage1::Start()
{
	PlayLevel::Start();

	// Sound
	GlobalUtils::SoundFileLoad("Penguin_Stage_BGM.wav", "Resources\\Sounds\\BGM");
	BGMVolume = 1.0f;

	CurrentStage = 1;
	NextLevelName = "Penguin_Stage2";
	CreateUIElements();
}

void Penguin_Stage1::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void Penguin_Stage1::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}