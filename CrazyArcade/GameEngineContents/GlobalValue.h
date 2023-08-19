#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <vector>


#define MAX_PLAYER_COUNT 2
#define MAX_PLAYER_LEVEL 4


enum class MapType
{
	Seal1,
	Seal2,
	Peng1,
	Peng2,
	Max,
};

enum class CharacterList
{
	Bazzi,
	Dao,
	Marid,
	Kephi,
	Ethi,
	Mos,
	Uni,
	Dizni,
	Su,
	HooU,
	Ray,
	Random,
	Max,
};


enum class AvailableCharacterList
{
	Bazzi,
	Dao,
	Marid,
	Kephi,
	Random,
	Max,
};


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

struct PlayerInfo
{
public:
	int PlayerLevel = 1;
	int CurrentExp = 0;
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

	static float4 ItemPosNormalize;
	
	static const float4 ItemSoketPos_Single_Pos;
	static const float4 ItemSoketPos_Multi_1P_Pos;
	static const float4 ItemSoketPos_Multi_2P_Pos;

	static int AllTextureIndex_X;

	static int GroundTextureIndex_Y;
	static int MovableBlockTextureIndex_Y;
	static int ImmovableBlockTextureIndex_Y;
	static int StructureTextureIndex_Y;

	static float4 TileStartPos;


	static std::vector<CharacterTrait> VecCharacterTraits;

	static MapType g_SelectMap;

	static int g_ActiveRoomCount;
	static CharacterList g_SelectCharacter;
	static AvailableCharacterList g_SelectAvailableCharacter1;
	static AvailableCharacterList g_SelectAvailableCharacter2;

	//static int g_Player1Level;
	//static int g_Player2Level;


	static float g_ChangeLevelFadeSpeed;
	static const int g_FadeScreenAlphaValue = 70;

	static std::vector<PlayerInfo> g_vecPlayerInfo;
	static const std::vector<int> g_ExpArr;

	static void Init();
protected:

private:

};

