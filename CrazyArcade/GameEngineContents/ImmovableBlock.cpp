#include "ImmovableBlock.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include "GlobalUtils.h"
#include "ContentsEnum.h"

ImmovableBlock::ImmovableBlock()
{
}

ImmovableBlock::~ImmovableBlock()
{
}

void ImmovableBlock::Init(int _Index)
{
	Index = _Index;

	GlobalUtils::SpriteFileLoad("Blocks.bmp", "Resources\\Textures\\Tile", 3, 1);
	Renderer = CreateRenderer(RenderOrder::Map);
	Renderer->SetSprite("Blocks.bmp", Index);
}

void ImmovableBlock::Start()
{

}
