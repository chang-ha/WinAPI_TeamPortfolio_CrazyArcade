#include "UITestStage3.h"

#include "GlobalValue.h"
#include "GameMapInfo.h"
#include "FadeObject.h"

UITestStage3::UITestStage3()
{
}

UITestStage3::~UITestStage3()
{
}

void UITestStage3::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevel::LevelStart(_PrevLevel);
}

void UITestStage3::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
}

void UITestStage3::Start()
{
	PlayLevel::Start();

	MapFileLoad("Penguin_Stage3.map");
	TileSetting();

	CurrentStage = 3;
	NextLevelName = "RoomLevel";
	CreateUIElements();
}

void UITestStage3::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void UITestStage3::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}