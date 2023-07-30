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
	GlobalUtils::SpriteFileLoad("Dao_Idle_Up.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Down.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Left.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Idle_Right.Bmp", "Resources\\Textures\\Character\\Dao\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Dao_Left.Bmp", "Resources\\Textures\\Character\\Dao\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Dao_Right.Bmp", "Resources\\Textures\\Character\\Dao\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Dao_Up.Bmp", "Resources\\Textures\\Character\\Dao\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Dao_Down.Bmp", "Resources\\Textures\\Character\\Dao\\", 8, 1);

	MainRenderer = CreateRenderer(RenderOrder::Character);
	MainRenderer->CreateAnimation("Dao_Idle_Up", "Dao_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Down", "Dao_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Left", "Dao_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Right", "Dao_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Left", "Dao_Left.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Right", "Dao_Right.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Up", "Dao_Up.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Down", "Dao_Down.Bmp");

	ChangeState(CharacterState::Idle);
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