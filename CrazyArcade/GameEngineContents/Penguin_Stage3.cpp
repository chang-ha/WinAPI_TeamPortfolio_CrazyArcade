#include "Penguin_Stage3.h"
#include "FadeObject.h"

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
}

void Penguin_Stage3::LevelEnd(GameEngineLevel* _NextLevel)
{

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