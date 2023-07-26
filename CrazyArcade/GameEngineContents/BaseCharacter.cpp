#include "BaseCharacter.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
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
	/*CreateSprite("Bazzi_Wait.Bmp", 3);
	CreateSprite("Bazzi_Left.Bmp", 6);
	CreateSprite("Bazzi_Right.Bmp", 6);
	CreateSprite("Bazzi_Up.Bmp", 8);
	CreateSprite("Bazzi_Down.Bmp", 8);

	MainRenderer = CreateRenderer(RenderOrder::Character);
	MainRenderer->CreateAnimation("Bazzi_Wait", "Bazzi_Wait.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Left", "Bazzi_Left.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Right", "Bazzi_Right.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Up", "Bazzi_Up.Bmp");
	MainRenderer->CreateAnimation("Bazzi_Move_Down", "Bazzi_Down.Bmp");

	ChangeState(CharacterState::Wait);*/
}

void BaseCharacter::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (true == GameEngineInput::IsDown('J'))
	{
		SwitchDebugData();
	}

	PosX = GetPos().X;
	PosY = GetPos().Y;
}

void BaseCharacter::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	if (true == IsDebugData)
	{
		std::string XText = "";
		XText += "Player Pos X : ";
		XText += std::to_string(PosX);
		TextOutA(dc, 2, 3, XText.c_str(), static_cast<int>(XText.size()));

		std::string YText = "";
		YText += "Player Pos Y : ";
		YText += std::to_string(PosY);
		TextOutA(dc, 2, 30, YText.c_str(), static_cast<int>(YText.size()));
	}
}

// 스프라이트 제작 함수
void BaseCharacter::CreateSprite(const std::string& _TextureName, int _XCount, int _YCount /*= 1*/)
{
	/*if (ResourcesManager::GetInst().FindSprite(_TextureName) == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Textures\\Character\\Bazzi\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath(_TextureName), _XCount, _YCount);
	}*/
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

// Pos를 타일맵의 Index로 변환해서 위치시키는 함수
void BaseCharacter::CharacterPosToIndex()
{

}

void BaseCharacter::ChangeAnimationState(const std::string& _StateName) {}