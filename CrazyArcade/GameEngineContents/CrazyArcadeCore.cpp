﻿#include <GameEnginePlatform/GameEngineWindow.h>

#include "CrazyArcadeCore.h"
#include "TestLevel.h"

CrazyArcadeCore::CrazyArcadeCore()
{

}

CrazyArcadeCore::~CrazyArcadeCore()
{

}

void CrazyArcadeCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1280, 720 });
	GameEngineCore::CreateLevel<TestLevel>("TestLevel");

	GameEngineCore::ChangeLevel("TestLevel");
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
