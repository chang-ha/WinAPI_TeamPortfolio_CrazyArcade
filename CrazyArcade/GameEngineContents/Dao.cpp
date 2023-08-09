#include "Dao.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

Dao::Dao()
{
}

Dao::~Dao()
{
}

void Dao::Start()
{
	BaseCharacter::Start();
	GlobalUtils::SpriteFileLoad("Dao_Ready.Bmp", "Resources\\Textures\\Character\\Dao\\", 17, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Up.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Down.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Left.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Right.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Left.Bmp", "Resources\\Textures\\Character\\Dao\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Dao_Right.Bmp", "Resources\\Textures\\Character\\Dao\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Dao_Up.Bmp", "Resources\\Textures\\Character\\Dao\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Dao_Down.Bmp", "Resources\\Textures\\Character\\Dao\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Dao_Bubble.Bmp", "Resources\\Textures\\Character\\Dao\\", 4, 1);
	GlobalUtils::SpriteFileLoad("Dao_FlashLong.Bmp", "Resources\\Textures\\Character\\Dao\\", 4, 1);
	GlobalUtils::SpriteFileLoad("Dao_FlashShort.Bmp", "Resources\\Textures\\Character\\Dao\\", 2, 1);
	GlobalUtils::SpriteFileLoad("Dao_Live.Bmp", "Resources\\Textures\\Character\\Dao\\", 5, 1);
	GlobalUtils::SpriteFileLoad("Dao_Die.Bmp", "Resources\\Textures\\Character\\Dao\\", 13, 1);
	GlobalUtils::SpriteFileLoad("Dao_Jump.Bmp", "Resources\\Textures\\Character\\Dao\\", 8, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Dao_Ready", "Dao_Ready.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Up", "Dao_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Down", "Dao_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Left", "Dao_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Right", "Dao_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Left", "Dao_Left.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Right", "Dao_Right.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Up", "Dao_Up.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Down", "Dao_Down.Bmp");
	MainRenderer->CreateAnimation("Dao_Bubble", "Dao_Bubble.Bmp");
	MainRenderer->CreateAnimation("Dao_FlashLong", "Dao_FlashLong.Bmp");
	MainRenderer->CreateAnimation("Dao_FlashShort", "Dao_FlashShort.Bmp");
	MainRenderer->CreateAnimation("Dao_Live", "Dao_Live.Bmp");
	MainRenderer->CreateAnimation("Dao_Die", "Dao_Die.Bmp");
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