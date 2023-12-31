﻿#include "BaseCharacter.h"
#include "Penguin.h"
#include "GlobalUtils.h"
#include "PlayLevel.h"
#include "GameMapInfo.h"
#include "GlobalUtils.h"

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

	// Sound
	GlobalUtils::SoundFileLoad("Locked_In_Bubble.wav", "Resources\\Sounds\\Character\\");
	GlobalUtils::SoundFileLoad("Character_Death.wav", "Resources\\Sounds\\Character\\");
	GlobalUtils::SoundFileLoad("Live.wav", "Resources\\Sounds\\Character\\");

	ShadowRenderer = CreateRenderer("Shadow.Bmp", RenderOrder::Shadow);
	ShadowRenderer->SetRenderPos(CHARACTERSHADOWPOS);
	ShadowRenderer->SetAlpha(GlobalValue::AllAlphaValue);

	{
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionPos(GetPos() + float4 CHARACTERCOLLISIONPOS);
		BodyCollision->SetCollisionScale(BODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}
}

void BaseCharacter::Update(float _Delta)
{
	CurTile = PlayLevel::CurPlayLevel->GetCurTileType(GetPos() + float4 FOOTPOS);

	BossCheck();

	if (true == GameEngineInput::IsDown('Z'))
	{
		NoDamageSwitch();
	}

	StateUpdate(_Delta);

	// 물풍선 설치
	if (PlayerNumber == PlayerNum::P1)
	{
		if (true == GameEngineInput::IsDown(VK_SPACE) && CurState == "Idle" && GetBombCount() > 0
			|| true == GameEngineInput::IsDown(VK_SPACE) && CurState == "Move" && GetBombCount() > 0)
		{
			PlayLevel::CurPlayLevel->SetBubble(GetPos() + float4 SETBUBBLEPOS, GetBombPower(), PlayerNumber);
		}
	}

	if (PlayerNumber == PlayerNum::P2)
	{
		if (true == GameEngineInput::IsDown(VK_RSHIFT) && CurState == "Idle" && GetBombCount() > 0
			|| true == GameEngineInput::IsDown(VK_RSHIFT) && CurState == "Move" && GetBombCount() > 0)
		{
			PlayLevel::CurPlayLevel->SetBubble(GetPos() + float4 SETBUBBLEPOS, GetBombPower(), PlayerNumber);
		}
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
		if (PlayerNumber == PlayerNum::P1)
		{
			std::string XText = "";
			XText += "Player Pos X : ";
			XText += std::to_string(GetPos().iX());
			TextOutA(dc, 2, 3, XText.c_str(), static_cast<int>(XText.size()));

			std::string YText = "";
			YText += "Player Pos Y : ";
			YText += std::to_string(GetPos().iY());
			TextOutA(dc, 2, 30, YText.c_str(), static_cast<int>(YText.size()));

			std::string BombCountText = "";
			BombCountText += "1P폭탄 수 : ";
			BombCountText += std::to_string(GetBombCount());
			TextOutA(dc, 2, 57, BombCountText.c_str(), static_cast<int>(BombCountText.size()));

			std::string BombPowerText = "";
			BombPowerText += "1P파워 : ";
			BombPowerText += std::to_string(GetBombPower());
			TextOutA(dc, 2, 84, BombPowerText.c_str(), static_cast<int>(BombPowerText.size()));

			std::string SpeedText = "";
			SpeedText += "1P속도 : ";
			SpeedText += std::to_string(static_cast<int>(GetSpeed()));
			TextOutA(dc, 2, 111, SpeedText.c_str(), static_cast<int>(SpeedText.size()));

			std::string CurTileNum = "";
			CurTileNum += "1P바늘 : ";
			CurTileNum += std::to_string(GetNeedle());
			TextOutA(dc, 2, 138, CurTileNum.c_str(), static_cast<int>(CurTileNum.size()));

			std::string ItemCount = "";
			ItemCount += "1P아이템 : ";
			ItemCount += std::to_string(GetItemCount);
			TextOutA(dc, 2, 165, ItemCount.c_str(), static_cast<int>(ItemCount.size()));

			std::string Kill = "";
			Kill += "1P Kill : ";
			Kill += std::to_string(KillCount);
			TextOutA(dc, 2, 192, Kill.c_str(), static_cast<int>(Kill.size()));

			std::string Save = "";
			Save += "1P Save : ";
			Save += std::to_string(SaveCount);
			TextOutA(dc, 2, 219, Save.c_str(), static_cast<int>(Save.size()));
		}

		if (PlayerNumber == PlayerNum::P2)
		{
			std::string XText = "";
			XText += "Player Pos X : ";
			XText += std::to_string(GetPos().iX());
			TextOutA(dc, 670, 3, XText.c_str(), static_cast<int>(XText.size()));

			std::string YText = "";
			YText += "Player Pos Y : ";
			YText += std::to_string(GetPos().iY());
			TextOutA(dc, 670, 30, YText.c_str(), static_cast<int>(YText.size()));

			std::string BombCountText = "";
			BombCountText += "2P폭탄 수 : ";
			BombCountText += std::to_string(GetBombCount());
			TextOutA(dc, 700, 57, BombCountText.c_str(), static_cast<int>(BombCountText.size()));

			std::string BombPowerText = "";
			BombPowerText += "2P파워 : ";
			BombPowerText += std::to_string(GetBombPower());
			TextOutA(dc, 700, 84, BombPowerText.c_str(), static_cast<int>(BombPowerText.size()));

			std::string SpeedText = "";
			SpeedText += "2P속도 : ";
			SpeedText += std::to_string(static_cast<int>(GetSpeed()));
			TextOutA(dc, 700, 111, SpeedText.c_str(), static_cast<int>(SpeedText.size()));

			std::string CurTileNum = "";
			CurTileNum += "2P바늘 : ";
			CurTileNum += std::to_string(GetNeedle());
			TextOutA(dc, 700, 138, CurTileNum.c_str(), static_cast<int>(CurTileNum.size()));

			std::string ItemCount = "";
			ItemCount += "2P아이템 : ";
			ItemCount += std::to_string(GetItemCount);
			TextOutA(dc, 700, 165, ItemCount.c_str(), static_cast<int>(ItemCount.size()));

			std::string Kill = "";
			Kill += "2P Kill : ";
			Kill += std::to_string(KillCount);
			TextOutA(dc, 700, 192, Kill.c_str(), static_cast<int>(Kill.size()));

			std::string Save = "";
			Save += "2P Save : ";
			Save += std::to_string(SaveCount);
			TextOutA(dc, 700, 219, Save.c_str(), static_cast<int>(Save.size()));
		}

		std::string NoDamageText = "";
		NoDamageText += "무적 : ";
		if (NoDamage == true)
		{
			NoDamageText += "True";
		}
		else
		{
			NoDamageText += "False";
		}
		TextOutA(dc, 2, 246, NoDamageText.c_str(), static_cast<int>(NoDamageText.size()));

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


		Data.Pos = GetPos() + float4 FOOTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 SETBUBBLEPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}
}

void BaseCharacter::GetItem(const ItemType& _ItemType)
{
	++GetItemCount;
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
		NeedlePlus();
		break;
	default:
		break;
	}
}

// 캐릭터 방향 변경 함수
void BaseCharacter::DirCheck()
{
	ActorDir CheckDir = Dir;

	if (PlayerNumber == PlayerNum::P1)
	{
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
	}
	
	if (PlayerNumber == PlayerNum::P2)
	{
		if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsPress(VK_LEFT))
		{
			CheckDir = ActorDir::Left;
		}
		if (true == GameEngineInput::IsDown(VK_RIGHT) || true == GameEngineInput::IsPress(VK_RIGHT))
		{
			CheckDir = ActorDir::Right;
		}
		if (true == GameEngineInput::IsDown(VK_UP) || true == GameEngineInput::IsPress(VK_UP))
		{
			CheckDir = ActorDir::Up;
		}
		if (true == GameEngineInput::IsDown(VK_DOWN) || true == GameEngineInput::IsPress(VK_DOWN))
		{
			CheckDir = ActorDir::Down;
		}
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

void BaseCharacter::SetPlayer2()
{
	PlayerNumber = PlayerNum::P2;

	BodyCollision = CreateCollision(CollisionOrder::PlayerBody2);
	BodyCollision->SetCollisionPos(GetPos());
	BodyCollision->SetCollisionScale(BODYCOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void BaseCharacter::BossCheck()
{
	if (Penguin::BossMonster == nullptr)
	{
		return;
	}

	if (true == NoDamage)
	{
		return;
	}

	if (MonsterState::Die_Ready == Penguin::BossMonster->GetState()
		|| MonsterState::Die_Bubble == Penguin::BossMonster->GetState()
		|| MonsterState::Die == Penguin::BossMonster->GetState())
	{
		return;
	}

	GameMapIndex CharacterIndex = PlayLevel::CurPlayLevel->GetCurIndex(GetPos() + float4 FOOTPOS);

	std::vector<std::vector<float4>> CheckTile = Penguin::BossMonster->GetBossTile();

	for (std::vector<float4> CheckTileArr : CheckTile)
	{
		for (float4 CheckPos : CheckTileArr)
		{
			GameMapIndex BossIndex = { CheckPos.iX(), CheckPos.iY() };

			if (BossIndex.X == CharacterIndex.X && BossIndex.Y == CharacterIndex.Y)
			{
				ChangeState(CharacterState::Die);
				return;
			}
		}
	}

	return;
}