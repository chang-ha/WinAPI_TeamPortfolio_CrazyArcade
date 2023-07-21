#include <GameEnginePlatform/GameEngineWindow.h>

#include "GlobalValue.h"

float4 GlobalValue::WinScale = {};

GlobalValue::GlobalValue()
{

}

GlobalValue::~GlobalValue()
{

}

void GlobalValue::Init()
{
	WinScale = GameEngineWindow::MainWindow.GetScale();
}
