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
	MainRenderer->CreateAnimation("PiratemonRed_Move_Down", "Pirate_Red_Move_Down.Bmp", -1, -1, 0.2f, true);
	MainRenderer->CreateAnimation("PiratemonRed_Move_Up", "Pirate_Red_Move_Up.Bmp", -1, -1, 0.2f, true);
	MainRenderer->CreateAnimation("PiratemonRed_Move_Right", "Pirate_Red_Move_Right.Bmp", -1, -1, 0.2f, true);
	MainRenderer->CreateAnimation("PiratemonRed_Move_Left", "Pirate_Red_Move_Left.Bmp", -1, -1, 0.2f, true);
	MainRenderer->CreateAnimation("PiratemonRed_Die", "Pirate_Red_Death.Bmp", -1, -1, 0.2f, false);

	MainRenderer->SetRenderPos({ 0, 20 });

	GlobalUtils::SpriteFileLoad("Shadow.Bmp", "Resources\\Textures\\Monster\\", 1, 1);
	ShadowRenderer = CreateRenderer("Shadow.bmp", RenderOrder::Shadow);
	ShadowRenderer->SetRenderPos(ShadowPos);

	ChangeState(MonsterState::Idle);
}

void Piratemon_red::Update(float _Delta)
{
	StateUpdate(_Delta);

	CurTile = PlayLevel::CurPlayLevel->GetGroundTile();
	CurTileType = PlayLevel::CurPlayLevel->GetCurTileType(GetPos() + float4 CENTERPOS);

	if (State != MonsterState::Die)
	{
		BaseMonster::CheckCollision();
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

void Piratemon_red::MoveUpdate(float _Delta)
{
	if (CurTileType == TileObjectOrder::PopRange)
	{
		ChangeState(MonsterState::Die);
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float Speed = 50.0f;

	if (Dir == ActorDir::Down)
	{
		MovePos = { 0.0f, Speed * _Delta };
		CheckPos = BOTPOS;
	}

	if (Dir == ActorDir::Up)
	{
		MovePos = { 0.0f, -Speed * _Delta };
		CheckPos = TOPPOS;
	}

	if (Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTPOS;
	}

	if (Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = RIGHTPOS;
	}

	CheckPos += GetPos();

	bool CheckTile = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos, _Delta);

	if (false == CheckTile)
	{
		AddPos(MovePos);
	}

	// 방향 전환
	else if (true == CheckTile)
	{
		RandomDir("Move");
	}
}

void Piratemon_red::DieStart()
{
	ChangeAnimationState("Die");
	MonsterEffectSound = GameEngineSound::SoundPlay("Pirate_Monster_Death.wav");
	MonsterEffectSound.SetVolume(1.0f);
	PlayLevel::CurPlayLevel->StageMonsterCountMinus();
}