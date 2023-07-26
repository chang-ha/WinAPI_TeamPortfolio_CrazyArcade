#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/TileMap.h>


#include "BackGround.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"
#include "GameMapInfo.h"
#include "Structure.h"

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void PlayLevel::Start()
{
	Back = CreateActor<BackGround>(UpdateOrder::Map);
	if (nullptr == Back)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	Back->Init("PlayPanel.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());

	// 타일 정보
	{
		TileInfo.assign(GlobalValue::MapTileIndex_Y, (std::vector<GameMapInfo>(GlobalValue::MapTileIndex_X, { 0, 1, 0 })));

		TileInfo[0][0].MapInfo = 1;
		TileInfo[0][0].StructureTextureInfo = 1;

		TileInfo[2][1].MapInfo = 1;
		TileInfo[0][0].StructureTextureInfo = 2;
		TileInfo[2][4].MapInfo = 2;
		TileInfo[2][7].MapInfo = 3;
	}

	//GameEnginePath FilePath;
	//FilePath.SetCurrentPath();
	//FilePath.MoveParentToExistsChild("Resources");
	//FilePath.MoveChild("Resources\\Textures\\Tile");

	//if (false == ResourcesManager::GetInst().IsLoadTexture("Grounds.bmp"))
	//{
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Grounds.bmp"));
	//	ResourcesManager::GetInst().CreateSpriteSheet("Grounds.bmp", 10, 1);
	//}
	GlobalUtils::SpriteFileLoad("Grounds.bmp", "Resources\\Textures\\Tile", 10, 1);

	// 타일 생성
	GameEngineRenderer* TileRenderer = nullptr;
	Structure* StructureActor = nullptr;

	if (nullptr == Tile)
	{
		Tile = CreateActor<TileMap>();
		Tile->CreateTileMap("Grounds.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::Map);

		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
			{
				TileRenderer = Tile->SetTile(X, Y, TileInfo[Y][X].GroundTextureInfo, Tile_StartPos);

				switch (TileInfo[Y][X].MapInfo)
				{
				case 1:
					StructureActor = CreateActor<Structure>(UpdateOrder::Map);
					StructureActor->Init(TileInfo[Y][X].StructureTextureInfo);
					StructureActor->SetPos(Tile->IndexToPos(X, Y) + Tile_StartPos + float4(20, 0));
					break;
				case 2:
					break;
				case 3:
					break;
				default:
					break;
				}
			}
		}
	}

	//// 구조물
	//if (nullptr == Structure)
	//{
	//	Structure = CreateActor<TileMap>();
	//	Structure->CreateTileMap("TownTile.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::StructureTile);

	//	Block = CreateActor<TileMap>();
	//	Block->CreateTileMap("TownTile.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::StructureTile);

	//	for (int X = 1; X < GlobalValue::MapTileIndex_X; X += 4)
	//	{
	//		TileRenderer = Structure->SetTile(X, 2, 1, Tile_StartPos);
	//		TileRenderer->SetRenderScale({ 40, 80 });
	//		TileRenderer->AddRenderPos({ 0, -20 });
	//	}
	//}


}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void PlayLevel::Render(float _Delta)
{

}