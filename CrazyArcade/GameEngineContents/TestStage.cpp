#include "TestStage.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include "GlobalValue.h"
#include "GlobalUtils.h"
#include "GameMapInfo.h"
#include "FadeObject.h"
#include "BaseCharacter.h"
#include "Item.h"
#include "Snowmon_black.h"
#include "Snowmon_red.h"
#include "Piratemon_black.h"
#include "Piratemon_red.h"
#include "Button.h"
#include <GameEngineCore/TileMap.h>


TestStage::TestStage()
{
}

TestStage::~TestStage()
{
}

void TestStage::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevel::LevelStart(_PrevLevel);

	PlayLevel::CurPlayLevel->GetPlayer()->SwitchChangeReadyToIdle();

	if (nullptr != PlayLevel::CurPlayLevel->GetPlayer2())
	{
		PlayLevel::CurPlayLevel->GetPlayer2()->SwitchChangeReadyToIdle();
	}

	if (Player != nullptr)
	{
		Player->SetPos(GroundTile->IndexToPos(11, 7));
	}
	else
	{
		MsgBoxAssert("1P가 생성되지 못 했습니다");
		return;
	}

	if (Player2 != nullptr)
	{
		Player2->SetPos(GroundTile->IndexToPos(13, 7));
	}

	// Map
	MapFileLoad("TestMap2.map");
	TileSetting();

	// BGM
	BGMPlayer = GameEngineSound::SoundPlay("Penguin_Stage_BGM.wav", 10000);
	BGMPlayer.SetVolume(BGMVolume);

	// 몬스터 테스트
	BaseMonster* Monster = CreateMonster<Snowmon_black>();
	Monster->SetPos(GroundTile->IndexToPos(1, 6));

	Monster = CreateMonster<Snowmon_red>();
	Monster->SetPos(GroundTile->IndexToPos(1, 7));

	Monster = CreateMonster<Piratemon_black>();
	Monster->SetPos(GroundTile->IndexToPos(1, 8));

	Monster = CreateMonster<Piratemon_red>();
	Monster->SetPos(GroundTile->IndexToPos(2, 7));

	// 아이템 테스트
	CreateItemInTile(3, 6, ItemType::Bubble);
	CreateItemInTile(8, 6, ItemType::Fluid);
	CreateItemInTile(4, 6, ItemType::Roller);
	CreateItemInTile(5, 6, ItemType::Needle);
	CreateItemInTile(6, 6, ItemType::Ultra);
	CreateItemInTile(7, 6, ItemType::Red_Devil);

	ItemSetting();

	SetItemInBlock(1, 0, ItemType::Needle);

	

	// UI
	CreatePortrait();

	ChangeStageStartValue(true);
}

void TestStage::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);
	ReleaseLevelComposition();

	//Monster->Death();
	//Monster = nullptr;
}

void TestStage::Start()
{
	PlayLevel::Start();

	// Sound
	GlobalUtils::SoundFileLoad("Penguin_Stage_BGM.wav", "Resources\\Sounds\\BGM");
	BGMVolume = 0.0f;

	// UI
	SetupGoBackButton();
}


void TestStage::SetupGoBackButton()
{
	m_GoBackButton = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == m_GoBackButton)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_GoBackButton->setRenderer(RenderOrder::FirstElementUI);
	m_GoBackButton->setButtonTexture(ButtonState::Normal, "Play_Button_Exit_Normal.bmp", "Resources\\Textures\\UI\\PlayStage", 1, 1);
	m_GoBackButton->setButtonTexture(ButtonState::Hover, "Play_Button_Exit_Hover.bmp", "Resources\\Textures\\UI\\PlayStage", 1, 2);
	m_GoBackButton->setButtonTexture(ButtonState::Click, "Play_Button_Exit_Click.bmp", "Resources\\Textures\\UI\\PlayStage", 1, 1);
	m_GoBackButton->setCallback<TestStage>(ButtonEventState::Click, this, &TestStage::clickGoBackButton);
	m_GoBackButton->setButtonSound(ButtonEventState::Hover, "Game_Exit_Button_Hover.wav", "Resources\\Sounds\\GamePlay");

	float4 ButtonScale = m_GoBackButton->getButtonScale();
	float4 ButtonPos = CONST_GoBackButtonStartPos + ButtonScale.Half();

	m_GoBackButton->SetPos(ButtonPos);
}

void TestStage::clickGoBackButton()
{
	FadeObject::CallFadeOut(this, "RoomLevel", GlobalValue::g_ChangeLevelFadeSpeed);
}



void TestStage::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void TestStage::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}