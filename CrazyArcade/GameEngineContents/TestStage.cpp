#include "TestStage.h"

#include "GlobalValue.h"
#include "GameMapInfo.h"
#include "FadeObject.h"

#include "Snowmon_black.h"

TestStage::TestStage()
{
}

TestStage::~TestStage()
{
}

void TestStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevel::LevelStart(_PrevLevel);
	FadeObject::CallFadeIn(this, 0.4f);
}

void TestStage::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestStage::Start()
{
	PlayLevel::Start();

	MapFileLoad("TestMap.map");
	TileSetting();

	// 몬스터 테스트
	Monster = CreateActor<Snowmon_black>();
	Monster->SetPos({ GlobalValue::WinScale.Half().X + 200, GlobalValue::WinScale.Half().Y });
}

void TestStage::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void TestStage::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}