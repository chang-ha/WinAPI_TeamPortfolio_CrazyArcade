#include <GameEngineCore/TileMap.h>

#include "Penguin_Stage3.h"
#include "FadeObject.h"
#include "Penguin.h"
#include "BaseCharacter.h"

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

	Player->SetPos(GroundTile->IndexToPos(8, 13));
	if (nullptr == Boss_Penguin)
	{
		Boss_Penguin = CreateActor<Penguin>();
	}
	Boss_Penguin->SetPos(GroundTile->IndexToPos(8, 5));
}

void Penguin_Stage3::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Boss_Penguin)
	{
		Boss_Penguin->Death();
	}
}

void Penguin_Stage3::Start()
{
	PlayLevel::Start();

	MapFileLoad("Penguin_Stage3.map");
	TileSetting();
}

void Penguin_Stage3::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void Penguin_Stage3::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}