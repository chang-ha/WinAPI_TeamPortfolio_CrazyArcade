#include "Piratemon_red.h"
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

Piratemon_red::Piratemon_red()
{
}

Piratemon_red::~Piratemon_red()
{
}

void Piratemon_red::Start()
{
	BaseMonster::Start();

	GlobalUtils::SpriteFileLoad("Pirate_Red_Idle_Down.Bmp", "Resources\\Textures\\Monster\\Pirate\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Red_Idle_Up.Bmp", "Resources\\Textures\\Monster\\Pirate\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Red_Idle_Right.Bmp", "Resources\\Textures\\Monster\\Pirate\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Red_Idle_Left.Bmp", "Resources\\Textures\\Monster\\Pirate\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Red_Move_Down.Bmp", "Resources\\Textures\\Monster\\Pirate\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Red_Move_Up.Bmp", "Resources\\Textures\\Monster\\Pirate\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Red_Move_Right.Bmp", "Resources\\Textures\\Monster\\Pirate\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Red_Move_Left.Bmp", "Resources\\Textures\\Monster\\Pirate\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Pirate_Red_Death.Bmp", "Resources\\Textures\\Monster\\Pirate\\Red\\", 4, 1);


	MainRenderer = CreateRenderer(RenderOrder::MapObject);

	MainRenderer->CreateAnimation("PiratemonRed_Idle_Down", "Pirate_Red_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("PiratemonRed_Idle_Up", "Pirate_Red_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("PiratemonRed_Idle_Right", "Pirate_Red_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("PiratemonRed_Idle_Left", "Pirate_Red_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("PiratemonRed_Move_Down", "Pirate_Red_Move_Down.Bmp");
	MainRenderer->CreateAnimation("PiratemonRed_Move_Up", "Pirate_Red_Move_Up.Bmp");
	MainRenderer->CreateAnimation("PiratemonRed_Move_Right", "Pirate_Red_Move_Right.Bmp");
	MainRenderer->CreateAnimation("PiratemonRed_Move_Left", "Pirate_Red_Move_Left.Bmp");
	MainRenderer->CreateAnimation("PiratemonRed_Death", "Pirate_Red_Death.Bmp");

}

void Piratemon_red::ChangeAnimationState(const std::string& _StateName)
{

}