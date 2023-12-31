﻿#include "Dao.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

Dao::Dao()
{
	MinSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MinSpeed;
	MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MaxSpeed;
	Speed = MinSpeed;

	MinBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MinBombPower;
	MaxBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MaxBombPower;
	BombPower = MinBombPower;

	MinBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MinWaterBombs;
	MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MaxWaterBombs;
	BombCount = MinBombCount;
}

Dao::~Dao()
{
}

void Dao::Start()
{
	BaseCharacter::Start();
	GlobalUtils::SpriteFileLoad("Dao_Ready.Bmp", "Resources\\Textures\\Character\\Dao\\", 18, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Up.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Down.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Left.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Right.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Left.Bmp", "Resources\\Textures\\Character\\Dao\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Dao_Right.Bmp", "Resources\\Textures\\Character\\Dao\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Dao_Up.Bmp", "Resources\\Textures\\Character\\Dao\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Dao_Down.Bmp", "Resources\\Textures\\Character\\Dao\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Dao_Bubble.Bmp", "Resources\\Textures\\Character\\Dao\\", 14, 1);
	GlobalUtils::SpriteFileLoad("Dao_FlashLong.Bmp", "Resources\\Textures\\Character\\Dao\\", 4, 1);
	GlobalUtils::SpriteFileLoad("Dao_FlashShort.Bmp", "Resources\\Textures\\Character\\Dao\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Dao_Live.Bmp", "Resources\\Textures\\Character\\Dao\\", 5, 1);
	GlobalUtils::SpriteFileLoad("Dao_Die.Bmp", "Resources\\Textures\\Character\\Dao\\", 11, 1);
	GlobalUtils::SpriteFileLoad("Dao_Jump.Bmp", "Resources\\Textures\\Character\\Dao\\", 8, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Dao_Ready", "Dao_Ready.Bmp", -1, -1, 0.1f, false);
	MainRenderer->CreateAnimation("Dao_Idle_Up", "Dao_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Down", "Dao_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Left", "Dao_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Right", "Dao_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Left", "Dao_Left.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Right", "Dao_Right.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Up", "Dao_Up.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Down", "Dao_Down.Bmp");
	MainRenderer->CreateAnimation("Dao_BubbleHit", "Dao_Bubble.Bmp", 0, 2, 0.1f, false);
	MainRenderer->CreateAnimation("Dao_Bubble", "Dao_Bubble.Bmp", 3, 11, 0.1f, true);
	MainRenderer->CreateAnimation("Dao_BubbleEnd", "Dao_Bubble.Bmp", 12, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Dao_FlashLong", "Dao_FlashLong.Bmp");
	MainRenderer->CreateAnimation("Dao_FlashShort", "Dao_FlashShort.Bmp");
	MainRenderer->CreateAnimation("Dao_Live", "Dao_Live.Bmp", -1, -1, 0.1f, false);
	MainRenderer->CreateAnimation("Dao_Die", "Dao_Die.Bmp", -1, -1, 0.1f, false);
	MainRenderer->CreateAnimation("Dao_Jump", "Dao_Jump.Bmp", -1, -1, 0.3f, true);

	ChangeState(CharacterState::Ready);
}

void Dao::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Dao_";

	AnimationName += _StateName;

	if (_StateName == "Move" || _StateName == "Idle")
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