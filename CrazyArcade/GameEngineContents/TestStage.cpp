#include "TestStage.h"

#include "GlobalValue.h"
#include "GameMapInfo.h"
#include "FadeObject.h"

#include "Item.h"
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
}

void TestStage::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestStage::Start()
{
	PlayLevel::Start();

	MapFileLoad("TestMap2.map");
	TileSetting();

	// 몬스터 테스트
	Monster = CreateActor<Snowmon_black>();
	Monster->SetPos({ GlobalValue::WinScale.Half().X + 200, GlobalValue::WinScale.Half().Y });

	// 아이템 테스트
	CreateItemInTile(3, 6, ItemType::Bubble);
	CreateItemInTile(8, 6, ItemType::Fluid);
	CreateItemInTile(4, 6, ItemType::Roller);
	CreateItemInTile(5, 6, ItemType::Needle);
	CreateItemInTile(6, 6, ItemType::Ultra);
	CreateItemInTile(7, 6, ItemType::Red_Devil);

	ItemSetting();
}

void TestStage::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void TestStage::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}