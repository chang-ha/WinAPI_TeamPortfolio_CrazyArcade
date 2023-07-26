﻿#include "PlayLevel.h"

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

	// 맵 스프라이트 로드
	GlobalUtils::SpriteFileLoad("Grounds.bmp", "Resources\\Textures\\Tile", 10, 1);
	GlobalUtils::SpriteFileLoad("Structures.bmp", "Resources\\Textures\\Tile", 4, 1);
	GlobalUtils::SpriteFileLoad("ImMovableBlocks.bmp", "Resources\\Textures\\Tile", 2, 1);
	GlobalUtils::SpriteFileLoad("MovableBlocks.bmp", "Resources\\Textures\\Tile", 1, 1);

	//TileInfo 초기화
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
				ObjectTile->SetTileToSprite(X, Y, TileInfo[Y][X].ObjectTextureInfo, "Structures.bmp", GlobalValue::TileStartPos + float4(0, -20));
				break;
			case TileObjectOrder::ImmovableBlock:
				ObjectTile->SetTileToSprite(X, Y, TileInfo[Y][X].ObjectTextureInfo, "ImmovableBlocks.bmp", GlobalValue::TileStartPos + float4(0, -2));
				break;
			case TileObjectOrder::MovableBlock:
				ObjectTile->SetTileToSprite(X, Y, TileInfo[Y][X].ObjectTextureInfo, "MovableBlocks.bmp", GlobalValue::TileStartPos + float4(0, -2));
				break;
			case TileObjectOrder::Item:
				break;
			default:
				break;
			}
		}
	}
}

