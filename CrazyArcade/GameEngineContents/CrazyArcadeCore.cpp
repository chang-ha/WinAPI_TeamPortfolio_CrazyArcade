#include <GameEnginePlatform/GameEngineWindow.h>

#include "CrazyArcadeCore.h"
#include "TitleLevel.h"
#include "GlobalValue.h"

CrazyArcadeCore::CrazyArcadeCore()
{

}

CrazyArcadeCore::~CrazyArcadeCore()
{

}

void CrazyArcadeCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1280, 720 });
	GlobalValue::Init();

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");

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
