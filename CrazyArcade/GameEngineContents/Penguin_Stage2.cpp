#include "Penguin_Stage2.h"
#include "FadeObject.h"
#include "BaseCharacter.h"
#include "Snowmon_black.h"
#include "Snowmon_red.h"
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

	// Player
	Player->SetPos(GroundTile->IndexToPos(2, 2));
	Player2->SetPos(GroundTile->IndexToPos(12, 2));

	// Snowmon Black
	Snowmon_black* Snowmon_Black = CreateActor<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(5, 1));
	Snowmon_Black->SetState(MonsterState::EggSummon);

	Snowmon_Black = CreateActor<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(2, 5));

	Snowmon_Black = CreateActor<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(2, 9));

	Snowmon_Black = CreateActor<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(11, 1));

	Snowmon_Black = CreateActor<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(14, 5));

	Snowmon_Black = CreateActor<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(14, 9));

	Snowmon_Black = CreateActor<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(5, 13));

	Snowmon_Black = CreateActor<Snowmon_black>();
	Snowmon_Black->SetPos(GroundTile->IndexToPos(11, 13));

	// Snowmon Red
	Snowmon_red* Snowmon_Red = CreateActor<Snowmon_red>();
	Snowmon_Red->SetPos(GroundTile->IndexToPos(7, 6));

	Snowmon_Red = CreateActor<Snowmon_red>();
	Snowmon_Red->SetPos(GroundTile->IndexToPos(9, 6));

	Snowmon_Red = CreateActor<Snowmon_red>();
	Snowmon_Red->SetPos(GroundTile->IndexToPos(7, 8));

	Snowmon_Red = CreateActor<Snowmon_red>();
	Snowmon_Red->SetPos(GroundTile->IndexToPos(9, 8));
}

void Penguin_Stage2::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Penguin_Stage2::Start()
{
	PlayLevel::Start();
	

	MapFileLoad("Penguin_Stage2.map");
	TileSetting();
}

void Penguin_Stage2::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void Penguin_Stage2::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}