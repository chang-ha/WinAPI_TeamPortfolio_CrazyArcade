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

	MapFileLoad("TestMap.map");
	TileSetting();

	// 몬스터 테스트
	Monster = CreateActor<Snowmon_black>();
	Monster->SetPos({ GlobalValue::WinScale.Half().X + 200, GlobalValue::WinScale.Half().Y });


	// 아이템 테스트
	TestItem = CreateActor<Item>(UpdateOrder::Map);
	TestItem->SetItemType(ItemType::Bubble);
	TestItem->AddPos({ (40 * 7), (40 * 7) });

	TestItem = CreateActor<Item>(UpdateOrder::Map);
	TestItem->SetItemType(ItemType::Fluid);
	TestItem->AddPos({ (40 * 8), (40 * 7) });

	TestItem = CreateActor<Item>(UpdateOrder::Map);
	TestItem->SetItemType(ItemType::Roller);
	TestItem->AddPos({ (40 * 9), (40 * 7) });

	TestItem = CreateActor<Item>(UpdateOrder::Map);
	TestItem->SetItemType(ItemType::Needle);
	TestItem->AddPos({ (40 * 10), (40 * 7) });

	TestItem = CreateActor<Item>(UpdateOrder::Map);
	TestItem->SetItemType(ItemType::Ultra);
	TestItem->AddPos({ (40 * 11), (40 * 7) });

	TestItem = CreateActor<Item>(UpdateOrder::Map);
	TestItem->SetItemType(ItemType::Red_Devil);
	TestItem->AddPos({ (40 * 12), (40 * 7) });
}

void TestStage::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void TestStage::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}