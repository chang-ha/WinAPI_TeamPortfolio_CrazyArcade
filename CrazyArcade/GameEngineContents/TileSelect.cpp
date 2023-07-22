#include "TileSelect.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "ContentsEnum.h"

TileSelect::TileSelect()
{
	
}

TileSelect::~TileSelect()
{
}

void TileSelect::Start()
{
	if (nullptr == Renderer)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Tile");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TileSelect.bmp"));

		Renderer = CreateRenderer(RenderOrder::SelectTile);
		Renderer->SetTexture("TileSelect.bmp");
	}
}

void TileSelect::Update(float _Delta)
{
}
