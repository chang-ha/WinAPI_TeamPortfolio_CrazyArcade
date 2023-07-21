#include "PlayLevel.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void PlayLevel::Start()
{
	Back = CreateActor<BackGround>(UpdateOrder::Map);
	Back->Init("PlayLevel.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());

	int a = 0;
}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void PlayLevel::Render(float _Delta)
{

}