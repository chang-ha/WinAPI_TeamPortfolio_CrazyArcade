#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/TileMap.h>


#include "BackGround.h"
#include "Dao.h"
#include "Bazzi.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "GameMapInfo.h"

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
		TileInfo[2][4].MapInfo = 2;
		TileInfo[2][7].MapInfo = 3;
	}


	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("Resources");
	FilePath.MoveChild("Resources\\Textures\\Tile");

	if (false == ResourcesManager::GetInst().IsLoadTexture("TownGround.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TownGround.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("TownGround.bmp", 10, 1);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("TownStructure.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TownStructure.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("TownStructure.bmp", 4, 1);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("TownBlock.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TownBlock.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("TownBlock.bmp", 3, 1);
	}

	// 타일 생성
	if (nullptr == Tile)
	{
		Tile = CreateActor<TileMap>();
		Tile->CreateTileMap("TownGround.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::GroundTile);

		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
			{
				TileRenderer = Tile->SetTile(X, Y, TileInfo[Y][X].GroundTextureInfo, Tile_StartPos);

				switch (TileInfo[Y][X].MapInfo)
				{
				case 1:
					
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

		// 테스트용 막혀야하는 타일 생성

		TileRenderer = Tile->SetTile(5, 5, 5, Tile_StartPos);
		TestTiles.push_back(TileRenderer);

		TileRenderer = Tile->SetTile(5, 8, 5, Tile_StartPos);
		TestTiles.push_back(TileRenderer);

		TileRenderer = Tile->SetTile(8, 5, 5, Tile_StartPos);
		TestTiles.push_back(TileRenderer);

		TileRenderer = Tile->SetTile(8, 8, 5, Tile_StartPos);
		TestTiles.push_back(TileRenderer);

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


	Check = CreateActor<Bazzi>(UpdateOrder::Character);
	Check->SetPos(GlobalValue::WinScale.Half());
}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	CheckTile();
}

void PlayLevel::Render(float _Delta)
{

}

// 플레이어랑 타일맵 인덱스 비교용 테스트 함수
void PlayLevel::CheckTile()
{
	// 플레이어 위치 400, 300
	// 플레이어 인덱스 9, 6

	if (nullptr != Check)
	{
		float4 PlayerPos = Check->GetPos();
		float4 PlayerIndex = Tile->PosToIndex(PlayerPos - GlobalValue::MapTileSize);
	
		if (nullptr != Check)
		{
			for (size_t i = 0; i < TestTiles.size(); i++)
			{
				GameEngineRenderer* TestTile = TestTiles[i];
				float4 CheckTestTilePos = TestTile->GetRenderPos();
				float4 CheckTestTIleIndex = Tile->PosToIndex(CheckTestTilePos - GlobalValue::MapTileSize);

				if (PlayerIndex.iX() == CheckTestTIleIndex.iX() && PlayerIndex.iY() == CheckTestTIleIndex.iY())
				{
					int a = 0;
				}
			}
		}
	}
}