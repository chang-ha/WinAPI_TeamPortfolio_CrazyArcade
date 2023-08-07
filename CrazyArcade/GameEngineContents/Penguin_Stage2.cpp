#include "Penguin_Stage2.h"
#include "FadeObject.h"
#include "BaseCharacter.h"

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