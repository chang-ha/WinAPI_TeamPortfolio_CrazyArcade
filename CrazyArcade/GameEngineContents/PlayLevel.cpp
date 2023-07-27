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
#include "GlobalUtils.h"
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

	// 맵 스프라이트 로드
	GlobalUtils::SpriteFileLoad("Grounds.bmp", "Resources\\Textures\\Tile", 10, 1);
	GlobalUtils::SpriteFileLoad("Structures.bmp", "Resources\\Textures\\Tile", 4, 1);
	GlobalUtils::SpriteFileLoad("ImMovableBlocks.bmp", "Resources\\Textures\\Tile", 2, 1);
	GlobalUtils::SpriteFileLoad("MovableBlocks.bmp", "Resources\\Textures\\Tile", 1, 1);

	//TileInfo 초기화
	TileInfo.assign(GlobalValue::MapTileIndex_Y, (std::vector<GameMapInfo>(GlobalValue::MapTileIndex_X, GameMapInfo::DefaultInfo)));

	// 캐릭터 생성
	Check = CreateActor<Dao>(UpdateOrder::Character);
	Check->SetPos(GlobalValue::WinScale.Half());
}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void PlayLevel::Render(float _Delta)
{

}

void PlayLevel::TileSetting()
{
	// TileInfo에 저장된 정보를 이용하여 타일맵 생성합니다.

	if (nullptr == GroundTile)
	{
		GroundTile = CreateActor<TileMap>();
		if (nullptr == GroundTile)
		{
			MsgBoxAssert("타일을 생성하지 못했습니다.");
			return;
		}

		GroundTile->CreateTileMap("Grounds.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::Map);
	}

	if (nullptr == ObjectTile)
	{

		ObjectTile = CreateActor<TileMap>();
		if (nullptr == ObjectTile)
		{
			MsgBoxAssert("타일을 생성하지 못했습니다.");
			return;
		}

		ObjectTile->CreateTileMap("Structures.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::Map);
	}

	GameEngineRenderer* TileRenderer = nullptr;

	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
		{
			GroundTile->SetTile(X, Y, TileInfo[Y][X].GroundTextureInfo, GlobalValue::TileStartPos);
			switch (TileInfo[Y][X].MapInfo)
			{
			case TileObjectOrder::Structure:
				ObjectTile->SetTileToSprite(X, Y, "Structures.bmp", TileInfo[Y][X].ObjectTextureInfo, GlobalValue::TileStartPos + float4(0, -20), true);
				break;
			case TileObjectOrder::ImmovableBlock:
				ObjectTile->SetTileToSprite(X, Y, "ImmovableBlocks.bmp", TileInfo[Y][X].ObjectTextureInfo, GlobalValue::TileStartPos + float4(0, -2), true);
				break;
			case TileObjectOrder::MovableBlock:
				ObjectTile->SetTileToSprite(X, Y, "MovableBlocks.bmp", TileInfo[Y][X].ObjectTextureInfo, GlobalValue::TileStartPos + float4(0, -2), true);
				break;
			case TileObjectOrder::Item:
				break;
			default:
				break;
			}
		}
	}
}

// 플레이어랑 타일맵 인덱스 비교용 테스트 함수
void PlayLevel::CheckTile()
{
	// 플레이어 위치 400, 300
	// 플레이어 인덱스 9, 6

	if (nullptr != Check)
	{
		float4 PlayerPos = Check->GetPos();
		/*float4 PlayerIndex = Tile->PosToIndex(PlayerPos - GlobalValue::MapTileSize);
	
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
		}*/
	}
}