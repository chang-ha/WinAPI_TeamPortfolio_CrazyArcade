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
}

Kephi::~Kephi()
{
}

void Kephi::Start()
{
	GlobalUtils::SpriteFileLoad("Kephi_Idle_Up.Bmp", "Resources\\Textures\\Character\\Kephi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Idle_Down.Bmp", "Resources\\Textures\\Character\\Kephi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Idle_Left.Bmp", "Resources\\Textures\\Character\\Kephi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Idle_Right.Bmp", "Resources\\Textures\\Character\\Kephi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Left.Bmp", "Resources\\Textures\\Character\\Kephi\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Right.Bmp", "Resources\\Textures\\Character\\Kephi\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Up.Bmp", "Resources\\Textures\\Character\\Kephi\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Kephi_Down.Bmp", "Resources\\Textures\\Character\\Kephi\\", 8, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Kephi_Idle_Up", "Kephi_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Kephi_Idle_Down", "Kephi_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Kephi_Idle_Left", "Kephi_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Kephi_Idle_Right", "Kephi_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Kephi_Move_Left", "Kephi_Left.Bmp");
	MainRenderer->CreateAnimation("Kephi_Move_Right", "Kephi_Right.Bmp");
	MainRenderer->CreateAnimation("Kephi_Move_Up", "Kephi_Up.Bmp");
	MainRenderer->CreateAnimation("Kephi_Move_Down", "Kephi_Down.Bmp");

	ChangeState(CharacterState::Idle);
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