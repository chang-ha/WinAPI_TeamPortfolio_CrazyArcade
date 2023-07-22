#include "BaseCharacter.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

BaseCharacter::BaseCharacter()
{
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Bazzi_Wait.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Textures\\Character\\Bazzi\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bazzi_Wait.Bmp"), 3, 1);
	}

	MainRenderer = CreateRenderer(RenderOrder::Character);
	MainRenderer->CreateAnimation("Bazzi_Wait", "Bazzi_Wait.Bmp");

	ChangeState(CharacterState::Wait);
}

void BaseCharacter::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BaseCharacter::Render(float _Delta)
{
	
}

void BaseCharacter::DirCheck()
{
	ActorDir CheckDir = Dir;

	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsPress('A'))
	{
		CheckDir = ActorDir::Left;
	}
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsPress('D'))
	{
		CheckDir = ActorDir::Right;
	}
	if (true == GameEngineInput::IsDown('W') || true == GameEngineInput::IsPress('W'))
	{
		CheckDir = ActorDir::Up;
	}
	if (true == GameEngineInput::IsDown('S') || true == GameEngineInput::IsPress('S'))
	{
		CheckDir = ActorDir::Down;
	}

	if (CheckDir != Dir)
	{
		Dir = CheckDir;
		ChangeAnimationState(CurState);
	}
}

void BaseCharacter::StateUpdate(float _Delta)
{
	switch (State)
	{
	case CharacterState::Wait:
		return WaitUpdate(_Delta);
	/*case CharacterState::Move:
		break;
	case CharacterState::Ready:
		break;
	case CharacterState::FlashLong:
		break;
	case CharacterState::FlashShort:
		break;
	case CharacterState::Trap:
		break;
	case CharacterState::Live:
		break;
	case CharacterState::Die:
		break;
	case CharacterState::Jump:
		break;*/
	default:
		break;
	}
}

void BaseCharacter::ChangeState(CharacterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case CharacterState::Wait:
			WaitStart();
			break;
		/*case CharacterState::Move:
			break;
		case CharacterState::Ready:
			break;
		case CharacterState::FlashLong:
			break;
		case CharacterState::FlashShort:
			break;
		case CharacterState::Trap:
			break;
		case CharacterState::Live:
			break;
		case CharacterState::Die:
			break;
		case CharacterState::Jump:
			break;*/
		default:
			break;
		}
	}

	State = _State;
}

void BaseCharacter::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Bazzi_";

	AnimationName += _StateName;

	if (_StateName == "Move")
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