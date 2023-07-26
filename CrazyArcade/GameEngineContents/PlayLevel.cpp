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

	TileInfo.assign(GlobalValue::MapTileIndex_Y, (std::vector<GameMapInfo>(GlobalValue::MapTileIndex_X, GameMapInfo::DefaultInfo)));
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
	// TileInfo에 저장된 정보를 이용하여 타일맵 생성
	if (nullptr == Tile)
	{
		GlobalUtils::SpriteFileLoad("Grounds.bmp", "Resources\\Textures\\Tile", 10, 1);

		Tile = CreateActor<TileMap>();
		if (nullptr == Tile)
		{
			MsgBoxAssert("타일을 생성하지 못했습니다.");
			return;
		}

		Tile->CreateTileMap("Grounds.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::Map);

		GameEngineRenderer* TileRenderer = nullptr;

		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
			{
				TileRenderer = Tile->SetTile(X, Y, TileInfo[Y][X].GroundTextureInfo, GlobalValue::TileStartPos);

				switch (TileInfo[Y][X].MapInfo)
				{
				case TileObjectOrder::Structure:
					break;
				case TileObjectOrder::ImmovableBlock:
					break;
				case TileObjectOrder::MovableBlock:
					break;
				case TileObjectOrder::Item:
					break;

				default:
					break;
				}
			}
		}
	}
}
