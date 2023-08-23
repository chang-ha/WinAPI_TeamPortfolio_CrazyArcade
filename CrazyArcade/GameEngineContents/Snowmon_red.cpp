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
	BaseMonster::Start();

	// Egg
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Egg_Summon.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 4, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_EggIdle_Down.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_EggIdle_Up.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_EggIdle_Left.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_EggIdle_Right.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_EggMove_Down.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_EggMove_Up.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_EggMove_Right.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_EggMove_Left.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Egg_Hatch.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 5, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Egg_Death.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\Egg\\", 6, 1);

	// Snowmon
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Idle_Down.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Idle_Up.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Idle_Left.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Idle_Right.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_AngerIdle_Down.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_AngerIdle_Left.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_AngerIdle_Right.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_AngerIdle_Up.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Move_Down.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Move_Up.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Move_Right.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Move_Left.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_AngerMove_Down.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_AngerMove_Up.Bmp",		"Resources\\Textures\\Monster\\Snowmon\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_AngerMove_Right.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_AngerMove_Left.Bmp",	"Resources\\Textures\\Monster\\Snowmon\\Red\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Freeze.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Red\\", 3, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Die.Bmp",				"Resources\\Textures\\Monster\\Snowmon\\Red\\", 3, 1);
	GlobalUtils::SpriteFileLoad("Snowmon_Red_Anger.Bmp",			"Resources\\Textures\\Monster\\Snowmon\\Red\\", 9, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);

	// Egg
	MainRenderer->CreateAnimation("Snowmon_Red_EggSummon",		"Snowmon_Red_Egg_Summon.Bmp", 0, 3, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_EggIdle_Down",	"Snowmon_Red_EggIdle_Down.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_EggIdle_Up",		"Snowmon_Red_EggIdle_Up.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_EggIdle_Left",	"Snowmon_Red_EggIdle_Left.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_EggIdle_Right",	"Snowmon_Red_EggIdle_Right.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_EggMove_Down",	"Snowmon_Red_EggMove_Down.Bmp", 0, 1, 0.4f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_EggMove_Up",		"Snowmon_Red_EggMove_Up.Bmp", 0, 1, 0.4f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_EggMove_Right",	"Snowmon_Red_EggMove_Right.Bmp", 0, 1, 0.4f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_EggMove_Left",	"Snowmon_Red_EggMove_Left.Bmp", 0, 1, 0.4f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_EggHatch",		"Snowmon_Red_Egg_Hatch.Bmp", 0, 4, 0.2f, false);
	MainRenderer->CreateAnimation("Snowmon_Red_EggDeath",		"Snowmon_Red_Egg_Death.Bmp", 0, 5, 0.1f, false);

	// Snowmon
	MainRenderer->CreateAnimation("Snowmon_Red_Idle_Down",	"Snowmon_Red_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_Idle_Up",	"Snowmon_Red_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_Idle_Left",	"Snowmon_Red_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_Idle_Right",	"Snowmon_Red_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_AngerIdle_Down",		"Snowmon_Red_AngerIdle_Down.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_AngerIdle_Up",		"Snowmon_Red_AngerIdle_Up.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_AngerIdle_Left",		"Snowmon_Red_AngerIdle_Left.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_AngerIdle_Right",	"Snowmon_Red_AngerIdle_Right.Bmp");
	MainRenderer->CreateAnimation("Snowmon_Red_Move_Down",		"Snowmon_Red_Move_Down.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_Move_Up",		"Snowmon_Red_Move_Up.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_Move_Right",		"Snowmon_Red_Move_Right.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_Move_Left",		"Snowmon_Red_Move_Left.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_AngerMove_Down",		"Snowmon_Red_AngerMove_Down.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_AngerMove_Up",		"Snowmon_Red_AngerMove_Up.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_AngerMove_Right",	"Snowmon_Red_AngerMove_Right.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_AngerMove_Left",		"Snowmon_Red_AngerMove_Left.Bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Snowmon_Red_Freeze",		"Snowmon_Red_Freeze.Bmp", 0, 2, 0.2f, false);
	MainRenderer->CreateAnimation("Snowmon_Red_Die",		"Snowmon_Red_Die.Bmp", 0, 2, 0.1f, false);
	MainRenderer->CreateAnimation("Snowmon_Red_Anger",		"Snowmon_Red_Anger.Bmp", 0, 8, 0.1f, false);

	MainRenderer->SetRenderPos({ 0, 15 });

	ChangeState(MonsterState::Idle);

	ShadowRenderer->SetRenderPos(ShadowPos);
}

void Snowmon_red::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Snowmon_Red_";

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