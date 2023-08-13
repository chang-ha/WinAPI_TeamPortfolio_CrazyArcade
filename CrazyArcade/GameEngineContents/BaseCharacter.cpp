#include "BaseCharacter.h"
#include "GlobalUtils.h"
#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/TileMap.h>

BaseCharacter::BaseCharacter()
{
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::Start()
{
	GlobalUtils::SpriteFileLoad("Shadow.Bmp", "Resources\\Textures\\Character\\", 1, 1);

	ShadowRenderer = CreateRenderer("Shadow.Bmp", RenderOrder::Shadow);
	ShadowRenderer->SetRenderPos(BOTCHECKPOS);

	{
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionPos(GetPos());
		BodyCollision->SetCollisionScale(BODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}
}

void BaseCharacter::Update(float _Delta)
{
	CurTile = PlayLevel::CurPlayLevel->GetCurTileType(GetPos());

	if (CurTile == TileObjectOrder::PopRange)
	{
		ChangeState(CharacterState::Bubble);
	}

	if (true == GameEngineInput::IsDown('K'))
	{
		ChangeState(CharacterState::Jump);
	}

	StateUpdate(_Delta);

	// 물풍선 설치
	if (true == GameEngineInput::IsDown(VK_SPACE) && CurState == "Idle" && GetBombCount() > 0
		|| true == GameEngineInput::IsDown(VK_SPACE) && CurState == "Move" && GetBombCount() > 0)
	{
		PlayLevel::CurPlayLevel->SetBubble({ GetPos().X, GetPos().Y + 5.0f}, GetBombPower());
	}

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

		std::string BombCountText = "";
		BombCountText += "폭탄 설치 개수 : ";
		BombCountText += std::to_string(GetBombCount());
		TextOutA(dc, 2, 57, BombCountText.c_str(), static_cast<int>(BombCountText.size()));

		std::string BombPowerText = "";
		BombPowerText += "폭탄 파워 : ";
		BombPowerText += std::to_string(GetBombPower());
		TextOutA(dc, 2, 84, BombPowerText.c_str(), static_cast<int>(BombPowerText.size()));

		std::string SpeedText = "";
		SpeedText += "속도 : ";
		SpeedText += std::to_string(GetSpeed());
		TextOutA(dc, 2, 111, SpeedText.c_str(), static_cast<int>(SpeedText.size()));

		std::string CurTileText = "";
		CurTileText += "밟고있는 타일 번호 : ";
		CurTileText += std::to_string(static_cast<int>(CurTile));
		TextOutA(dc, 2, 138, CurTileText.c_str(), static_cast<int>(CurTileText.size()));

		CollisionData Data;

		Data.Pos = GetPos();
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


		Data.Pos = GetPos() + float4 TOPCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 LEFTTOPCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 RIGHTTOPCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


		Data.Pos = GetPos() + float4 LEFTCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 LEFTMOVETOPCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 LEFTMOVEBOTCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


		Data.Pos = GetPos() + float4 RIGHTCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 RIGHTMOVETOPCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 RIGHTMOVEBOTCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


		Data.Pos = GetPos() + float4 BOTCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 LEFTBOTCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 RIGHTBOTCHECKPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}
}

void BaseCharacter::GetItem(ItemType _ItemType)
{
	switch (_ItemType)
	{
	case ItemType::Bubble:
		BombCountPlus();
		break;
	case ItemType::Fluid:
		BombPowerPlus();
		break;
	case ItemType::Roller:
		SpeedUp();
		break;
	case ItemType::Ultra:
		ChangeMaxBombPower();
		break;
	case ItemType::Red_Devil:
		ChangeMaxSpeed();
		break;
	case ItemType::Needle:
		break;
	default:
		break;
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
	case CharacterState::BubbleHit:
		return BubbleHitUpdate(_Delta);
	case CharacterState::Bubble:
		return BubbleUpdate(_Delta);
	case CharacterState::BubbleEnd:
		return BubbleEndUpdate(_Delta);
	case CharacterState::Ready:
		return ReadyUpdate(_Delta);
	case CharacterState::FlashLong:
		return FlashLongUpdate(_Delta);
	case CharacterState::FlashShort:
		return FlashShortUpdate(_Delta);
	case CharacterState::Live:
		return LiveUpdate(_Delta);
	case CharacterState::Die:
		return DieUpdate(_Delta);
	case CharacterState::Jump:
		return JumpUpdate(_Delta);
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
		case CharacterState::BubbleHit:
			BubbleHitStart();
			break;
		case CharacterState::Bubble:
			BubbleStart();
			break;
		case CharacterState::BubbleEnd:
			BubbleEndStart();
			break;
		case CharacterState::Ready:
			ReadyStart();
			break;
		case CharacterState::FlashLong:
			FlashLongStart();
			break;
		case CharacterState::FlashShort:
			FlashShortStart();
			break;
		case CharacterState::Live:
			LiveStart();
			break;
		case CharacterState::Die:
			DieStart();
			break;
		case CharacterState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void BaseCharacter::ChangeAnimationState(const std::string& _StateName) {}