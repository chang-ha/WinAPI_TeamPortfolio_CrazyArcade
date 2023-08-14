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
#include <GameEngineCore/GameEngineCollision.h>
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
	MainRenderer->CreateAnimation("PiratemonRed_Die", "Pirate_Red_Death.Bmp");

	GlobalUtils::SpriteFileLoad("Shadow.Bmp", "Resources\\Textures\\Monster\\", 1, 1);
	ShadowRenderer = CreateRenderer("Shadow.bmp", RenderOrder::Shadow);
	ShadowRenderer->SetRenderPos(ShadowPos);

	MonsterCollision->SetCollisionPos({ 0.0f, 5.0f });

	ChangeState(MonsterState::Idle);
}

void Piratemon_red::Update(float _Delta)
{
	StateUpdate(_Delta);

	CurTile = PlayLevel::CurPlayLevel->GetGroundTile();
	CurTileType = PlayLevel::CurPlayLevel->GetCurTileType(GetPos());

	if (CurTileType == TileObjectOrder::PopRange)
	{
		ChangeState(MonsterState::Die);
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		SwitchDebugData();
	}
}

void Piratemon_red::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "PiratemonRed_";

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

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}