#include "TitleLevel.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TitleLevel::Start()
{
	ContentLevel::Start();

	Back = CreateActor<BackGround>(UpdateOrder::Map);
	Back->Init("TitleLevel.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());
}

void TitleLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TitleLevel::Render(float _Delta)
{

}