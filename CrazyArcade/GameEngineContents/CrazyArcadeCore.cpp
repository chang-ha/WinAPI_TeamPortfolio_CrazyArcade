#include <GameEnginePlatform/GameEngineWindow.h>

#include "CrazyArcadeCore.h"
#include "GlobalValue.h"
#include "TitleLevel.h"
#include "TestStage.h"
#include "MapEditor.h"
#include "RoomLevel.h"
#include "UITestStage.h"
#include "UITestStage2.h"
#include "UITestStage3.h"
#include "TitleLodumani.h"
#include "TitleNexon.h"

#include "Penguin_Stage1.h"
#include "Penguin_Stage2.h"
#include "Penguin_Stage3.h"

CrazyArcadeCore::CrazyArcadeCore()
{

}

CrazyArcadeCore::~CrazyArcadeCore()
{

}

void CrazyArcadeCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 800, 600 });
	GlobalValue::Init();

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<TestStage>("TestStage");
	GameEngineCore::CreateLevel<MapEditor>("MapEditor");
	GameEngineCore::CreateLevel<RoomLevel>("RoomLevel");
	GameEngineCore::CreateLevel<Penguin_Stage1>("Penguin_Stage1");
	GameEngineCore::CreateLevel<Penguin_Stage2>("Penguin_Stage2");
	GameEngineCore::CreateLevel<Penguin_Stage3>("Penguin_Stage3");
	GameEngineCore::CreateLevel<UITestStage>("UITestStage");
	GameEngineCore::CreateLevel<UITestStage2>("UITestStage2");
	GameEngineCore::CreateLevel<UITestStage3>("UITestStage3");
	GameEngineCore::CreateLevel<TitleNexon>("TitleNexon");
	GameEngineCore::CreateLevel<TitleLodumani>("TitleLodumani");
	
	GameEngineCore::ChangeLevel("Penguin_Stage1");
}

void CrazyArcadeCore::Update(float _Delta)
{

}

void CrazyArcadeCore::Render(float _Delta)
{

}

void CrazyArcadeCore::Release()
{

}
