#include "Kephi.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

Kephi::Kephi()
{
	MinSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MinSpeed;
	MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MaxSpeed;
	Speed = MinSpeed;

	MinBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MinBombPower;
	MaxBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MaxBombPower;
	BombPower = MinBombPower;

	MinBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MinWaterBombs;
	MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MaxWaterBombs;
	BombCount = MinBombCount;
}

Kephi::~Kephi()
{
}

void Kephi::Start()
{
	BaseCharacter::Start();
	GlobalUtils::SpriteFileLoad("Kephi_Ready.Bmp", "Resources\\Textures\\Character\\Kephi\\", 18, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Idle_Up.Bmp", "Resources\\Textures\\Character\\Kephi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Idle_Down.Bmp", "Resources\\Textures\\Character\\Kephi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Idle_Left.Bmp", "Resources\\Textures\\Character\\Kephi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Idle_Right.Bmp", "Resources\\Textures\\Character\\Kephi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Left.Bmp", "Resources\\Textures\\Character\\Kephi\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Right.Bmp", "Resources\\Textures\\Character\\Kephi\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Up.Bmp", "Resources\\Textures\\Character\\Kephi\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Down.Bmp", "Resources\\Textures\\Character\\Kephi\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Bubble.Bmp", "Resources\\Textures\\Character\\Kephi\\", 14, 1);
	GlobalUtils::SpriteFileLoad("Kephi_FlashLong.Bmp", "Resources\\Textures\\Character\\Kephi\\", 4, 1);
	GlobalUtils::SpriteFileLoad("Kephi_FlashShort.Bmp", "Resources\\Textures\\Character\\Kephi\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Live.Bmp", "Resources\\Textures\\Character\\Kephi\\", 5, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Die.Bmp", "Resources\\Textures\\Character\\Kephi\\", 11, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Jump.Bmp", "Resources\\Textures\\Character\\Kephi\\", 2, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Kephi_Ready", "Kephi_Ready.Bmp", -1, -1, 0.1f, false);
	MainRenderer->CreateAnimation("Kephi_Idle_Up", "Kephi_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Kephi_Idle_Down", "Kephi_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Kephi_Idle_Left", "Kephi_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Kephi_Idle_Right", "Kephi_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Kephi_Move_Left", "Kephi_Left.Bmp");
	MainRenderer->CreateAnimation("Kephi_Move_Right", "Kephi_Right.Bmp");
	MainRenderer->CreateAnimation("Kephi_Move_Up", "Kephi_Up.Bmp");
	MainRenderer->CreateAnimation("Kephi_Move_Down", "Kephi_Down.Bmp");
	MainRenderer->CreateAnimation("Kephi_BubbleHit", "Kephi_Bubble.Bmp", 0, 2, 0.1f, false);
	MainRenderer->CreateAnimation("Kephi_Bubble", "Kephi_Bubble.Bmp", 3, 11, 0.1f, true);
	MainRenderer->CreateAnimation("Kephi_BubbleEnd", "Kephi_Bubble.Bmp", 12, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Kephi_FlashLong", "Kephi_FlashLong.Bmp");
	MainRenderer->CreateAnimation("Kephi_FlashShort", "Kephi_FlashShort.Bmp");
	MainRenderer->CreateAnimation("Kephi_Live", "Kephi_Live.Bmp", -1, -1, 0.1f, false);
	MainRenderer->CreateAnimation("Kephi_Die", "Kephi_Die.Bmp", -1, -1, 0.1f, false);
	MainRenderer->CreateAnimation("Kephi_Jump", "Kephi_Jump.Bmp", -1, -1, 0.3f, true);

	ChangeState(CharacterState::Ready);
}

void Kephi::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Kephi_";

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