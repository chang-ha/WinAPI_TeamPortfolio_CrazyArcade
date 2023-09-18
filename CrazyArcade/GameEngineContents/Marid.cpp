#include "Marid.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

Marid::Marid()
{
	MinSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MinSpeed;
	MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MaxSpeed;
	Speed = MinSpeed;

	MinBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MinBombPower;
	MaxBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MaxBombPower;
	BombPower = MinBombPower;

	MinBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MinWaterBombs;
	MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MaxWaterBombs;
	BombCount = MinBombCount;
}

Marid::~Marid()
{
}

void Marid::Start()
{
	BaseCharacter::Start();
	GlobalUtils::SpriteFileLoad("Marid_Ready.Bmp", "Resources\\Textures\\Character\\Marid\\", 18, 1);
	GlobalUtils::SpriteFileLoad("Marid_Idle_Up.Bmp", "Resources\\Textures\\Character\\Marid\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Marid_Idle_Down.Bmp", "Resources\\Textures\\Character\\Marid\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Marid_Idle_Left.Bmp", "Resources\\Textures\\Character\\Marid\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Marid_Idle_Right.Bmp", "Resources\\Textures\\Character\\Marid\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Marid_Left.Bmp", "Resources\\Textures\\Character\\Marid\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Marid_Right.Bmp", "Resources\\Textures\\Character\\Marid\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Marid_Up.Bmp", "Resources\\Textures\\Character\\Marid\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Marid_Down.Bmp", "Resources\\Textures\\Character\\Marid\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Marid_Bubble.Bmp", "Resources\\Textures\\Character\\Marid\\", 14, 1);
	GlobalUtils::SpriteFileLoad("Marid_FlashLong.Bmp", "Resources\\Textures\\Character\\Marid\\", 4, 1);
	GlobalUtils::SpriteFileLoad("Marid_FlashShort.Bmp", "Resources\\Textures\\Character\\Marid\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Marid_Live.Bmp", "Resources\\Textures\\Character\\Marid\\", 5, 1);
	GlobalUtils::SpriteFileLoad("Marid_Die.Bmp", "Resources\\Textures\\Character\\Marid\\", 11, 1);
	GlobalUtils::SpriteFileLoad("Marid_Jump.Bmp", "Resources\\Textures\\Character\\Marid\\", 8, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Marid_Ready", "Marid_Ready.Bmp", -1, -1, 0.1f, false);
	MainRenderer->CreateAnimation("Marid_Idle_Up", "Marid_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Marid_Idle_Down", "Marid_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Marid_Idle_Left", "Marid_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Marid_Idle_Right", "Marid_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Marid_Move_Left", "Marid_Left.Bmp");
	MainRenderer->CreateAnimation("Marid_Move_Right", "Marid_Right.Bmp");
	MainRenderer->CreateAnimation("Marid_Move_Up", "Marid_Up.Bmp");
	MainRenderer->CreateAnimation("Marid_Move_Down", "Marid_Down.Bmp");
	MainRenderer->CreateAnimation("Marid_BubbleHit", "Marid_Bubble.Bmp", 0, 2, 0.1f, false);
	MainRenderer->CreateAnimation("Marid_Bubble", "Marid_Bubble.Bmp", 3, 11, 0.1f, true);
	MainRenderer->CreateAnimation("Marid_BubbleEnd", "Marid_Bubble.Bmp", 12, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Marid_FlashLong", "Marid_FlashLong.Bmp");
	MainRenderer->CreateAnimation("Marid_FlashShort", "Marid_FlashShort.Bmp");
	MainRenderer->CreateAnimation("Marid_Live", "Marid_Live.Bmp", -1, -1, 0.1f, false);
	MainRenderer->CreateAnimation("Marid_Die", "Marid_Die.Bmp", -1, -1, 0.1f, false);
	MainRenderer->CreateAnimation("Marid_Jump", "Marid_Jump.Bmp", -1, -1, 0.3f, true);

	ChangeState(CharacterState::Ready);
}

void Marid::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Marid_";

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