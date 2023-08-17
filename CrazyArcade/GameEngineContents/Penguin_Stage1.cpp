#include "Penguin_Stage1.h"
#include "FadeObject.h"
#include "BaseCharacter.h"
#include "Snowmon_black.h"
#include "Piratemon_black.h"
#include "Piratemon_red.h"
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

	Player->SetPos(GroundTile->IndexToPos(6, 4));
	Player2->SetPos(GroundTile->IndexToPos(6, 10));

	Snowmon = CreateActor<Piratemon_black>(UpdateOrder::Monster);
	Snowmon->SetPos(GroundTile->IndexToPos(1, 6));

	Snowmon = CreateActor<Piratemon_black>(UpdateOrder::Monster);
	Snowmon->SetPos(GroundTile->IndexToPos(15, 6));

	Snowmon = CreateActor<Piratemon_red>(UpdateOrder::Monster);
	Snowmon->SetPos(GroundTile->IndexToPos(1, 8));

	Snowmon = CreateActor<Piratemon_red>(UpdateOrder::Monster);
	Snowmon->SetPos(GroundTile->IndexToPos(15, 8));
}

void Penguin_Stage1::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
}

void Penguin_Stage1::Start()
{
	PlayLevel::Start();

	MapFileLoad("Penguin_Stage1.map");
	TileSetting();
}

void Penguin_Stage1::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void Penguin_Stage1::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}