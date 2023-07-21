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
	Back = CreateActor<BackGround>(UpdateOrder::Map);
	Back->Init("Title.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());
}

void TitleLevel::Update(float _Delta)
{

}

void TitleLevel::Render(float _Delta)
{

}