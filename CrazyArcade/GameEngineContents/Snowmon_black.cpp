#include "Snowmon_black.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

Snowmon_black::Snowmon_black()
{
}

Snowmon_black::~Snowmon_black()
{
}

void Snowmon_black::Start()
{
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Down.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Up.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Right.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Left.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Freeze.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\", 3, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Melt.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\", 3, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Anger.Bmp", "Resources\\Textures\\Monster\\Snowmon\\", 9, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Snowmon_Black_Down",		"Snowmon_Black_Down.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_Up",		"Snowmon_Black_Up.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_Right",	"Snowmon_Black_Right.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_Left",		"Snowmon_Black_Left.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_Freeze",	"Snowmon_Black_Freeze.Bmp", 0, 2, 0.2f, false);
	MainRenderer->CreateAnimation("Snowmon_Black_Melt",		"Snowmon_Black_Melt.Bmp", 0, 2, 0.2f, false);
	MainRenderer->CreateAnimation("Snowmon_Black_Anger",	"Snowmon_Black_Anger.Bmp", 0, 8, 0.1f, false);


	MainRenderer->ChangeAnimation("Snowmon_Black_Down");
	//ChangeState(MonsterState::Idle);
}