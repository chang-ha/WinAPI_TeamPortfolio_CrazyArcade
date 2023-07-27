#include <GameEnginePlatform/GameEngineWindow.h>

#include "GlobalValue.h"

float4 GlobalValue::WinScale = {};
float4 GlobalValue::MapTileSize = {40, 40};
float4 GlobalValue::TileStartPos = { 20, 41 };
float4 GlobalValue::StructureTileSize = { 40, 80 };
int GlobalValue::MapTileIndex_X = 15;
int GlobalValue::MapTileIndex_Y = 13;


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
