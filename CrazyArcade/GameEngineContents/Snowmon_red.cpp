#include "Snowmon_red.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

Snowmon_red::Snowmon_red()
{
}

Snowmon_red::~Snowmon_red()
{
}

void Snowmon_red::Start()
{
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Down.Bmp",	 "Resources\\Textures\\Monster\\Snowmon\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Up.Bmp",	 "Resources\\Textures\\Monster\\Snowmon\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Right.Bmp", "Resources\\Textures\\Monster\\Snowmon\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Left.Bmp",	 "Resources\\Textures\\Monster\\Snowmon\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Freeze.Bmp","Resources\\Textures\\Monster\\Snowmon\\", 3, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Melt.Bmp",	 "Resources\\Textures\\Monster\\Snowmon\\", 3, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Snowmon_Red_Down",	 "Snowmon_Red_Down.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_Up",		 "Snowmon_Red_Up.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_Right",	 "Snowmon_Red_Right.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_Left",	 "Snowmon_Red_Left.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_Freeze",	 "Snowmon_Red_Freeze.Bmp", 0, 2, 0.2f, false);
	MainRenderer->CreateAnimation("Snowmon_Red_Melt",	 "Snowmon_Red_Melt.Bmp", 0, 2, 0.2f, false);

	MainRenderer->ChangeAnimation("Snowmon_Red_Down");
	//ChangeState(MonsterState::Idle);
}