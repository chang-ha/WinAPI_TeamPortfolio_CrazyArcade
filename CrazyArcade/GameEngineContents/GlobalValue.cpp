#include <GameEnginePlatform/GameEngineWindow.h>

#include "GlobalValue.h"
#include "ActorEnum.h"

float4 GlobalValue::WinScale = {};
float4 GlobalValue::MapTileSize = {40, 40};
float4 GlobalValue::TileStartPos = { 20, 41 };

float4 GlobalValue::StructureOverSize = { 0, 20 };
float4 GlobalValue::BlockOverSize = { 0, 5 };

float4 GlobalValue::ItemPosNormalize = { 20 , 0 };

int GlobalValue::AllTextureIndex_X = 3;

int GlobalValue::GroundTextureIndex_Y = 4;
int GlobalValue::StructureTextureIndex_Y = 2;
int GlobalValue::MovableBlockTextureIndex_Y = 1;
int GlobalValue::ImmovableBlockTextureIndex_Y = 1;


float4 GlobalValue::MapTileIndex = {15, 13};

int GlobalValue::MapTileIndex_X = 15;
int GlobalValue::MapTileIndex_Y = 13;

std::vector<CharacterTrait> GlobalValue::VecCharacterTraits;

MapType GlobalValue::g_SelectMap = MapType::Max;

int GlobalValue::g_ActiveRoomCount = 0;
CharacterList GlobalValue::g_SelectCharacter = CharacterList::Max;
AvailableCharacterList GlobalValue::g_SelectAvailableCharacter1 = AvailableCharacterList::Max;
AvailableCharacterList GlobalValue::g_SelectAvailableCharacter2 = AvailableCharacterList::Max;

//int GlobalValue::g_Player1Level = 1;
//int GlobalValue::g_Player2Level = 2;
std::vector<PlayerInfo> GlobalValue::g_vecPlayerInfo;

const std::vector<int> GlobalValue::g_ExpArr = { 300, 400, 500 };

float GlobalValue::g_ChangeLevelFadeSpeed = 0.3f;


GlobalValue::GlobalValue()
{

}

GlobalValue::~GlobalValue()
{

}

void GlobalValue::Init()
{
	WinScale = GameEngineWindow::MainWindow.GetScale();


	VecCharacterTraits.resize(static_cast<int>(CharacterList::Max));

	VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)] = { 1, 6, 1, 7, 5, 9 };
	VecCharacterTraits[static_cast<int>(CharacterList::Dao)] = { 1, 10, 1, 7, 5, 7 };
	VecCharacterTraits[static_cast<int>(CharacterList::Marid)] = { 2, 9, 1, 6, 4, 8 };
	VecCharacterTraits[static_cast<int>(CharacterList::Kephi)] = { 1, 9, 1, 8, 4, 8 };
	VecCharacterTraits[static_cast<int>(CharacterList::Ethi)] = { 1, 10, 1, 8, 4, 8 };
	VecCharacterTraits[static_cast<int>(CharacterList::Mos)] = { 1, 8, 1, 5, 5, 8 };
	VecCharacterTraits[static_cast<int>(CharacterList::Uni)] = { 1, 6, 2, 7, 5, 8 };
	VecCharacterTraits[static_cast<int>(CharacterList::Dizni)] = { 2, 7, 1, 9, 4, 8 };
	VecCharacterTraits[static_cast<int>(CharacterList::Su)] = { 2, 9, 1, 7, 6, 10 };
	VecCharacterTraits[static_cast<int>(CharacterList::HooU)] = { 3, 9, 1, 7, 5, 10 };
	VecCharacterTraits[static_cast<int>(CharacterList::Ray)] = { 2, 9, 1, 7, 5, 10 };
	VecCharacterTraits[static_cast<int>(CharacterList::Random)] = { 0, 0, 0, 0, 0, 0 };

	g_vecPlayerInfo.resize(MAX_PLAYER_COUNT);
}
