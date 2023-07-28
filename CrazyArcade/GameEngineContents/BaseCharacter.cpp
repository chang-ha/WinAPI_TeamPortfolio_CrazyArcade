#include "BaseCharacter.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

BaseCharacter::BaseCharacter()
{
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (true == GameEngineInput::IsDown('J'))
	{
		SwitchDebugData();
	}
}

void BaseCharacter::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	if (true == IsDebugData)
	{
		std::string XText = "";
		XText += "Player Pos X : ";
		XText += std::to_string(GetPos().X);
		TextOutA(dc, 2, 3, XText.c_str(), static_cast<int>(XText.size()));

		std::string YText = "";
		YText += "Player Pos Y : ";
		YText += std::to_string(GetPos().Y);
		TextOutA(dc, 2, 30, YText.c_str(), static_cast<int>(YText.size()));

		CollisionData Data;

		Data.Pos = GetPos();
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 BOTCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 LEFTCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 RIGHTCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}
}

// 캐릭터 방향 변경 함수
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
	case CharacterState::Idle:
		return IdleUpdate(_Delta);
	case CharacterState::Move:
		return MoveUpdate(_Delta);
	/*case CharacterState::Ready:
		break;
	case CharacterState::FlashLong:
		break;
	case CharacterState::FlashShort:
		break;
	case CharacterState::Bubble:
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
		case CharacterState::Idle:
			IdleStart();
			break;
		case CharacterState::Move:
			MoveStart();
			break;
		/*case CharacterState::Ready:
			break;
		case CharacterState::FlashLong:
			break;
		case CharacterState::FlashShort:
			break;
		case CharacterState::Bubble:
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

// Pos를 타일맵의 Index로 변환해서 위치시키는 함수
void BaseCharacter::CharacterPosToIndex() {}

void BaseCharacter::ChangeAnimationState(const std::string& _StateName) {}