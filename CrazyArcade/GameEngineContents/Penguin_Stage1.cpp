#include "Penguin_Stage1.h"
#include "FadeObject.h"

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
}

void Penguin_Stage1::LevelEnd(GameEngineLevel* _NextLevel)
{

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