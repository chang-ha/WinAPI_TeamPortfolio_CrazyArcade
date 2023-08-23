#include "Piratemon_black.h"
#include "BaseCharacter.h"
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
	MainRenderer->CreateAnimation("PiratemonBlack_Move_Down", "Pirate_Black_Move_Down.Bmp", -1, -1, 0.2f, true);
	MainRenderer->CreateAnimation("PiratemonBlack_Move_Up", "Pirate_Black_Move_Up.Bmp", -1, -1, 0.2f, true);
	MainRenderer->CreateAnimation("PiratemonBlack_Move_Right", "Pirate_Black_Move_Right.Bmp", -1, -1, 0.2f, true);
	MainRenderer->CreateAnimation("PiratemonBlack_Move_Left", "Pirate_Black_Move_Left.Bmp", -1, -1, 0.2f, true);
	MainRenderer->CreateAnimation("PiratemonBlack_Die", "Pirate_Black_Death.Bmp", -1, -1, 0.2f, false);

	MainRenderer->SetRenderPos({ 0, 15 });

	ShadowRenderer->SetRenderPos(ShadowPos);

	ChangeState(MonsterState::Idle);
}

void Piratemon_black::Update(float _Delta)
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

	TrackingTileUpdate();
}

void Piratemon_black::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "PiratemonBlack_";

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

void Piratemon_black::MoveUpdate(float _Delta)
{
	if (CurTileType == TileObjectOrder::PopRange)
	{
		//KillCountPlus();
		ChangeState(MonsterState::Die);
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float Speed = 50.0f;

	CheckPlayerTracking();

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

void Piratemon_black::DieStart()
{
	ChangeAnimationState("Die");
	MonsterEffectSound = GameEngineSound::SoundPlay("Pirate_Monster_Death.wav");
	if (true == IsDeathSound)
	{
		MonsterEffectSound.SetVolume(0.6f);
	}
	else
	{
		MonsterEffectSound.SetVolume(0.0f);
	}
}