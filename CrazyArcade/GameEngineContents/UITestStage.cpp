#include "UITestStage.h"

#include "GlobalValue.h"
#include "GameMapInfo.h"
#include "FadeObject.h"

UITestStage::UITestStage()
{
}

UITestStage::~UITestStage()
{
}

void UITestStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevel::LevelStart(_PrevLevel);
	FadeObject::CallFadeIn(this, 0.4f);
}

void UITestStage::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void UITestStage::Start()
{
	PlayLevel::Start();

	MapFileLoad("Penguin_Stage1.map");
	TileSetting();
}

void UITestStage::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void UITestStage::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}