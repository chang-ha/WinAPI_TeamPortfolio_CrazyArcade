#include "TestStage.h"

#include "GlobalValue.h"
#include "GameMapInfo.h"

TestStage::TestStage()
{
}

TestStage::~TestStage()
{
}

void TestStage::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TestStage::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestStage::Start()
{
	PlayLevel::Start();

	MapFileLoad("TestMap.map");
	TileSetting();
}

void TestStage::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void TestStage::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}