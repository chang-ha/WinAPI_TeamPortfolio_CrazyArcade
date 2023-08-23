#include "Snowmon_black.h"
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

Snowmon_black::Snowmon_black()
{
}

Snowmon_black::~Snowmon_black()
{
}

void Snowmon_black::Start()
{
	BaseMonster::Start();
	// Egg
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Egg_Summon.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 4, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_EggIdle_Down.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_EggIdle_Up.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_EggIdle_Left.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_EggIdle_Right.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_EggMove_Down.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_EggMove_Up.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_EggMove_Right.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_EggMove_Left.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Egg_Hatch.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 5, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Egg_Death.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Black\\Egg\\", 6, 1);

	// Snowmon
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Idle_Down.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Idle_Up.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Idle_Left.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Idle_Right.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_AngerIdle_Down.Bmp", "Resources\\Textures\\Monster\\Snowmon\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_AngerIdle_Left.Bmp", "Resources\\Textures\\Monster\\Snowmon\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_AngerIdle_Right.Bmp","Resources\\Textures\\Monster\\Snowmon\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_AngerIdle_Up.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\Black\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Move_Down.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Move_Up.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Move_Right.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Move_Left.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_AngerMove_Down.Bmp", "Resources\\Textures\\Monster\\Snowmon\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_AngerMove_Up.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_AngerMove_Right.Bmp","Resources\\Textures\\Monster\\Snowmon\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_AngerMove_Left.Bmp", "Resources\\Textures\\Monster\\Snowmon\\Black\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Freeze.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Black\\", 3, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Die.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Black\\", 3, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Anger.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Black\\", 9, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);

	// Egg
	MainRenderer->CreateAnimation("Snowmon_Black_EggSummon",		"Snowmon_Black_Egg_Summon.Bmp", 0, 3, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_EggIdle_Down",		"Snowmon_Black_EggIdle_Down.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_EggIdle_Up",		"Snowmon_Black_EggIdle_Up.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_EggIdle_Left",		"Snowmon_Black_EggIdle_Left.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_EggIdle_Right",	"Snowmon_Black_EggIdle_Right.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_EggMove_Down",		"Snowmon_Black_EggMove_Down.Bmp", 0, 1, 0.4f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_EggMove_Up",		"Snowmon_Black_EggMove_Up.Bmp", 0, 1, 0.4f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_EggMove_Right",	"Snowmon_Black_EggMove_Right.Bmp", 0, 1, 0.4f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_EggMove_Left",		"Snowmon_Black_EggMove_Left.Bmp", 0, 1, 0.4f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_EggHatch",			"Snowmon_Black_Egg_Hatch.Bmp", 0, 4, 0.2f, false);
	MainRenderer->CreateAnimation("Snowmon_Black_EggDeath",			"Snowmon_Black_Egg_Death.Bmp", 0, 5, 0.1f, false);

	// Snowmon
	MainRenderer->CreateAnimation("Snowmon_Black_Idle_Down",	"Snowmon_Black_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_Idle_Up",		"Snowmon_Black_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_Idle_Left",	"Snowmon_Black_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_Idle_Right",	"Snowmon_Black_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_AngerIdle_Down",	"Snowmon_Black_AngerIdle_Down.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_AngerIdle_Up",		"Snowmon_Black_AngerIdle_Up.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_AngerIdle_Left",	"Snowmon_Black_AngerIdle_Left.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_AngerIdle_Right",	"Snowmon_Black_AngerIdle_Right.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Black_Move_Down",	"Snowmon_Black_Move_Down.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_Move_Up",		"Snowmon_Black_Move_Up.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_Move_Right",	"Snowmon_Black_Move_Right.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_Move_Left",	"Snowmon_Black_Move_Left.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_AngerMove_Down",	"Snowmon_Black_AngerMove_Down.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_AngerMove_Up",		"Snowmon_Black_AngerMove_Up.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_AngerMove_Right",	"Snowmon_Black_AngerMove_Right.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_AngerMove_Left",	"Snowmon_Black_AngerMove_Left.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Black_Freeze",		"Snowmon_Black_Freeze.Bmp", 0, 2, 0.2f, false);
	MainRenderer->CreateAnimation("Snowmon_Black_Die",			"Snowmon_Black_Die.Bmp", 0, 2, 0.1f, false);
	MainRenderer->CreateAnimation("Snowmon_Black_Anger",		"Snowmon_Black_Anger.Bmp", 0, 8, 0.1f, false);
	
	MainRenderer->SetRenderPos({0, 18});

	ChangeState(MonsterState::Idle);

	ShadowRenderer->SetRenderPos(ShadowPos);
}


void Snowmon_black::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Snowmon_Black_";

	AnimationName += _StateName;

	if (_StateName == "Idle" || _StateName == "Move")
	{
		switch (Dir)
		{
		case ActorDir::Left:
			AnimationName += "_Left";
			break;
		case ActorDir::Right:
			AnimationName += "_Right";
			break;
		case ActorDir::Up:
			AnimationName += "_Up";
			break;
		case ActorDir::Down:
			AnimationName += "_Down";
			break;
		default:
			break;
		}
	}

	if (_StateName == "AngerIdle" || _StateName == "AngerMove")
	{
		switch (Dir)
		{
		case ActorDir::Left:
			AnimationName += "_Left";
			break;
		case ActorDir::Right:
			AnimationName += "_Right";
			break;
		case ActorDir::Up:
			AnimationName += "_Up";
			break;
		case ActorDir::Down:
			AnimationName += "_Down";
			break;
		default:
			break;
		}
	}

	if (_StateName == "EggIdle" || _StateName == "EggMove")
	{
		switch (Dir)
		{
		case ActorDir::Left:
			AnimationName += "_Left";
			break;
		case ActorDir::Right:
			AnimationName += "_Right";
			break;
		case ActorDir::Up:
			AnimationName += "_Up";
			break;
		case ActorDir::Down:
			AnimationName += "_Down";
			break;
		default:
			break;
		}
	}

	CurState = _StateName;
	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->ChangeAnimation(AnimationName);
}