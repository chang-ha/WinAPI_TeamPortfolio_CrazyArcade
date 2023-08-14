#include "Piratemon_black.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"
#include "ActorEnum.h"
#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/TileMap.h>

Piratemon_black::Piratemon_black()
{
}

Piratemon_black::~Piratemon_black()
{
}

void Piratemon_black::Start()
{
	BaseMonster::Start();

	GlobalUtils::SpriteFileLoad("Pirate_Black_Idle_Down.Bmp", "Resources\\Textures\\Monster\\Pirate\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Black_Idle_Up.Bmp", "Resources\\Textures\\Monster\\Pirate\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Black_Idle_Right.Bmp", "Resources\\Textures\\Monster\\Pirate\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Black_Idle_Left.Bmp", "Resources\\Textures\\Monster\\Pirate\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Black_Move_Down.Bmp", "Resources\\Textures\\Monster\\Pirate\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Black_Move_Up.Bmp", "Resources\\Textures\\Monster\\Pirate\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Black_Move_Right.Bmp", "Resources\\Textures\\Monster\\Pirate\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Black_Move_Left.Bmp", "Resources\\Textures\\Monster\\Pirate\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Black_Death.Bmp", "Resources\\Textures\\Monster\\Pirate\\Black\\", 4, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);

	MainRenderer->CreateAnimation("PiratemonBlack_Idle_Down", "Pirate_Black_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("PiratemonBlack_Idle_Up", "Pirate_Black_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("PiratemonBlack_Idle_Right", "Pirate_Black_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("PiratemonBlack_Idle_Left", "Pirate_Black_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("PiratemonBlack_Move_Down", "Pirate_Black_Move_Down.Bmp");
	MainRenderer->CreateAnimation("PiratemonBlack_Move_Up", "Pirate_Black_Move_Up.Bmp");
	MainRenderer->CreateAnimation("PiratemonBlack_Move_Right", "Pirate_Black_Move_Right.Bmp");
	MainRenderer->CreateAnimation("PiratemonBlack_Move_Left", "Pirate_Black_Move_Left.Bmp");
	MainRenderer->CreateAnimation("PiratemonBlack_Death", "Pirate_Black_Death.Bmp");
}

void Piratemon_black::ChangeAnimationState(const std::string& _StateName)
{

}