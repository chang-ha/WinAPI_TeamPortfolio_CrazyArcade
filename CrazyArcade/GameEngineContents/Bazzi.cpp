#include "Bazzi.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

Bazzi::Bazzi()
{
}

Bazzi::~Bazzi()
{
}

void Bazzi::Start()
{
	BaseCharacter::Start();
	GlobalUtils::SpriteFileLoad("Bazzi_Ready.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 17, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Idle_Up.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Idle_Down.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Idle_Left.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Idle_Right.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Left.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Right.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Up.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Down.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Bubble.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 14, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_FlashLong.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 4, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_FlashShort.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Live.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 5, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Die.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 11, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Jump.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 8, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Bazzi_Ready", "Bazzi_Ready.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Idle_Up", "Bazzi_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Idle_Down", "Bazzi_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Idle_Left", "Bazzi_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Idle_Right", "Bazzi_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Left", "Bazzi_Left.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Right", "Bazzi_Right.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Up", "Bazzi_Up.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Down", "Bazzi_Down.Bmp");
	MainRenderer->CreateAnimation("Bazzi_BubbleHit", "Bazzi_Bubble.Bmp", 0, 2, 0.1f, false);
	MainRenderer->CreateAnimation("Bazzi_Bubble", "Bazzi_Bubble.Bmp", 3, 11, 0.1f, true);
	MainRenderer->CreateAnimation("Bazzi_BubbleEnd", "Bazzi_Bubble.Bmp", 12, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Bazzi_FlashLong", "Bazzi_FlashLong.Bmp");
	MainRenderer->CreateAnimation("Bazzi_FlashShort", "Bazzi_FlashShort.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Live", "Bazzi_Live.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Die", "Bazzi_Die.Bmp", -1, -1, 0.1f, false);
	MainRenderer->CreateAnimation("Bazzi_Jump", "Bazzi_Jump.Bmp", -1, -1, 0.3f, true);

	ChangeState(CharacterState::Ready);
}

void Bazzi::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Bazzi_";

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