#include "Structure.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include "GlobalUtils.h"
#include "ContentsEnum.h"

Structure::Structure()
{
}

Structure::~Structure()
{
}

void Structure::Init(int _Index)
{
	Index = _Index;

	GlobalUtils::SpriteFileLoad("Structures.bmp", "Resources\\Textures\\Tile", 4, 1);

	Renderer = CreateRenderer(RenderOrder::Map);
	//Renderer->CreateAnimation("Idle", "Structures.bmp", Index, Index, 100.0f, false);
	//Renderer->ChangeAnimation("Idle");
	Renderer->SetSprite("Structures.bmp", 1);



}

void Structure::Start()
{

}
