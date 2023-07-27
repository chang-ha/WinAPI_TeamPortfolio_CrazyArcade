#include "Bazzi.h"
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
	CreateSprite("Bazzi_Idle_Up.Bmp", 1);
	CreateSprite("Bazzi_Idle_Down.Bmp", 1);
	CreateSprite("Bazzi_Idle_Left.Bmp", 1);
	CreateSprite("Bazzi_Idle_Right.Bmp", 1);
	CreateSprite("Bazzi_Left.Bmp", 6);
	CreateSprite("Bazzi_Right.Bmp", 6);
	CreateSprite("Bazzi_Up.Bmp", 8);
	CreateSprite("Bazzi_Down.Bmp", 8);
	
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

void Bazzi::CreateSprite(const std::string& _TextureName, int _XCount, int _YCount /*= 1*/)
{
	if (ResourcesManager::GetInst().FindSprite(_TextureName) == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Textures\\Character\\Bazzi\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath(_TextureName), _XCount, _YCount);
	}
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