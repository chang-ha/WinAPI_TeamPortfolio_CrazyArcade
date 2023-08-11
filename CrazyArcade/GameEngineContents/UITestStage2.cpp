#include "UITestStage2.h"

#include "GlobalValue.h"
#include "GameMapInfo.h"
#include "FadeObject.h"

UITestStage2::UITestStage2()
{
}

UITestStage2::~UITestStage2()
{
}

void UITestStage2::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevel::LevelStart(_PrevLevel);
}

void UITestStage2::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
}

void UITestStage2::Start()
{
	PlayLevel::Start();

	MapFileLoad("Penguin_Stage2.map");
	TileSetting();

	CurrentStage = 2;
	NextLevelName = "UITestStage3";
	CreateUIElements();
}

void UITestStage2::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void UITestStage2::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}