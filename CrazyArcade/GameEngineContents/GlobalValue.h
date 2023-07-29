#pragma once

#include <GameEngineBase/GameEngineMath.h>
class GlobalValue
{
public:
	// constructer destructer
	GlobalValue();
	~GlobalValue();

	// delete function
	GlobalValue(const GlobalValue& _Ohter) = delete;
	GlobalValue(GlobalValue&& _Ohter) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _Other) = delete;
	GlobalValue& operator=(GlobalValue&& _Other) noexcept = delete;

	static float4 WinScale;

	static int MapTileIndex_X;
	static int MapTileIndex_Y;
	static float4 MapTileSize;

	static float4 BlockOverSize;
	static float4 StructureOverSize;

	static float4 TileStartPos;

	static void Init();
protected:

private:

};

