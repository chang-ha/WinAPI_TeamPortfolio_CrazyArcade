#pragma once

#include <GameEngineBase/GameEngineMath.h>
#include <vector>


struct CharacterTrait
{
public:
	int MinWaterBombs = 0;
	int MaxWaterBombs = 0;
	int MinBombPower = 0;
	int MaxBombPower = 0;
	int MinSpeed = 0;
	int MaxSpeed = 0;
};


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

	static float4 MapTileIndex;
	static float4 MapTileSize;

	static float4 BlockOverSize;
	static float4 StructureOverSize;

	static int AllTextureIndex_X;

	static int GroundTextureIndex_Y;
	static int MovableBlockTextureIndex_Y;
	static int ImmovableBlockTextureIndex_Y;
	static int StructureTextureIndex_Y;

	static float4 TileStartPos;


	static std::vector<CharacterTrait> VecCharacterTraits;

	static void Init();
protected:

private:

};

