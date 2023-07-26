#include <GameEnginePlatform/GameEngineWindow.h>

#include "CrazyArcadeCore.h"
#include "GlobalValue.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "MapEditor.h"
#include "RoomLevel.h"


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
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<MapEditor>("MapEditor");
	GameEngineCore::CreateLevel<RoomLevel>("RoomLevel");
	

	GameEngineCore::ChangeLevel("TitleLevel");
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
