#include "Penguin.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>

Penguin::Penguin()
{
}

Penguin::~Penguin()
{
}

void Penguin::Start()
{
	GlobalUtils::SpriteFileLoad("Bazzi_Idle_Up.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 1, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Bazzi_Idle_Up", "Bazzi_Idle_Up.Bmp");
}