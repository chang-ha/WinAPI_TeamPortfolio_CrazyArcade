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
	GlobalUtils::SpriteFileLoad("Bazzi_Idle_Up.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Idle_Down.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Idle_Left.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Idle_Right.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Left.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Right.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Up.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Bazzi_Down.Bmp", "Resources\\Textures\\Character\\Bazzi\\", 8, 1);

	MainRenderer = CreateRenderer(RenderOrder::Character);
	MainRenderer->CreateAnimation("Bazzi_Idle_Up", "Bazzi_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Idle_Down", "Bazzi_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Idle_Left", "Bazzi_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Idle_Right", "Bazzi_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Left", "Bazzi_Left.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Right", "Bazzi_Right.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Up", "Bazzi_Up.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Down", "Bazzi_Down.Bmp");

	ChangeState(CharacterState::Idle);
}

void Bazzi::Update(float _Delta)
{
	BaseCharacter::Update(_Delta);
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