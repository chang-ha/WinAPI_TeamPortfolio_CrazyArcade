#include "Cappi.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

Cappi::Cappi()
{
}

Cappi::~Cappi()
{
}

void Cappi::Start()
{
	GlobalUtils::SpriteFileLoad("Cappi_Idle_Up.Bmp", "Resources\\Textures\\Character\\Cappi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Cappi_Idle_Down.Bmp", "Resources\\Textures\\Character\\Cappi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Cappi_Idle_Left.Bmp", "Resources\\Textures\\Character\\Cappi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Cappi_Idle_Right.Bmp", "Resources\\Textures\\Character\\Cappi\\", 1, 1);
	GlobalUtils::SpriteFileLoad("Cappi_Left.Bmp", "Resources\\Textures\\Character\\Cappi\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Cappi_Right.Bmp", "Resources\\Textures\\Character\\Cappi\\", 6, 1);
	GlobalUtils::SpriteFileLoad("Cappi_Up.Bmp", "Resources\\Textures\\Character\\Cappi\\", 8, 1);
	GlobalUtils::SpriteFileLoad("Cappi_Down.Bmp", "Resources\\Textures\\Character\\Cappi\\", 8, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Cappi_Idle_Up", "Cappi_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Cappi_Idle_Down", "Cappi_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Cappi_Idle_Left", "Cappi_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Cappi_Idle_Right", "Cappi_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Cappi_Move_Left", "Cappi_Left.Bmp");
	MainRenderer->CreateAnimation("Cappi_Move_Right", "Cappi_Right.Bmp");
	MainRenderer->CreateAnimation("Cappi_Move_Up", "Cappi_Up.Bmp");
	MainRenderer->CreateAnimation("Cappi_Move_Down", "Cappi_Down.Bmp");

	ChangeState(CharacterState::Idle);
}

void Cappi::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Cappi_";

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