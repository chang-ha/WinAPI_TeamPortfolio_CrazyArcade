#include "BaseMonster.h"
#include "GlobalUtils.h"
#include "PlayLevel.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/TileMap.h>

BaseMonster::BaseMonster()
{
}

BaseMonster::~BaseMonster()
{
}

void BaseMonster::Start() 
{

}

void BaseMonster::Update(float _Delta)
{
	StateUpdate(_Delta);

	CurTile = PlayLevel::CurPlayLevel->GetGroundTile();
	CurTileType = PlayLevel::CurPlayLevel->GetCurTileType(GetPos());

	if (CurTileType == TileObjectOrder::PopRange)
	{
		ChangeState(MonsterState::Freeze);
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		SwitchDebugData();
	}
}

void BaseMonster::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	if (true == IsDebugData)
	{
		CollisionData Data;

		Data.Pos = GetPos();
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 TOPPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 BOTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 LEFTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 RIGHTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}
}

void BaseMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	case MonsterState::Move:
		return MoveUpdate(_Delta);
	case MonsterState::Freeze:
		return FreezeUpdate(_Delta);
	case MonsterState::Anger:
		return AngerUpdate(_Delta);
	case MonsterState::AngerIdle:
		return AngerIdleUpdate(_Delta);
	case MonsterState::AngerMove:
		return AngerMoveUpdate(_Delta);
	case MonsterState::Die:
		return DieUpdate(_Delta);
	default:
		break;
	}
}

void BaseMonster::ChangeState(MonsterState _State)
{
	switch (_State)
	{
	case MonsterState::Idle:
		IdleStart();
		break;
	case MonsterState::Move:
		MoveStart();
		break;
	case MonsterState::Freeze:
		FreezeStart();
		break;
	case MonsterState::Anger:
		AngerStart();
		break;
	case MonsterState::AngerIdle:
		AngerIdleStart();
		break;
	case MonsterState::AngerMove:
		AngerMoveStart();
		break;
	case MonsterState::Die:
		DieStart();
		break;
	default:
		break;
	}

	State = _State;
}

void BaseMonster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void BaseMonster::IdleUpdate(float _Delta)
{
	static float IdleTimer = 0.0f;

	if (IdleTimer > 2.0f)
	{
		IdleTimer = 0.0f;
		ChangeState(MonsterState::Move);
		return;
	}

	IdleTimer += _Delta;
}

void BaseMonster::MoveStart()
{
	ChangeAnimationState("Move");
}

void BaseMonster::MoveUpdate(float _Delta)
{
	static float MoveTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	

	if (Dir == ActorDir::Down)
	{
		MovePos = { 0.0f, Speed * _Delta };
		CheckPos = BOTPOS;
	}

	if (Dir == ActorDir::Up)
	{
		MovePos = { 0.0f, -Speed * _Delta };
		CheckPos = TOPPOS;
	}

	if (Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTPOS;
	}

	if (Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = RIGHTPOS;
	}

	CheckPos += GetPos();

	bool CheckTile = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos, _Delta);

	if (false == CheckTile)
	{
		AddPos(MovePos);
	}
	
	// 방향 전환
	else if (true == CheckTile)
	{
		RandomDir("Move");
	}

	MoveTimer += _Delta;
}

void BaseMonster::FreezeStart()
{
	ChangeAnimationState("Freeze");
}

void BaseMonster::FreezeUpdate(float _Delta)
{
	ChangeState(MonsterState::Freeze);

	static float FreezeTimer = 0.0f;

	if (FreezeTimer > 5.0f)
	{
		FreezeTimer = 0.0f;
		ChangeState(MonsterState::Anger);
		return;
	}

	FreezeTimer += _Delta;
}

void BaseMonster::AngerStart()
{
	ChangeAnimationState("Anger");
}

void BaseMonster::AngerUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::AngerIdle);
	}
}

void BaseMonster::AngerIdleStart()
{
	ChangeAnimationState("AngerIdle");
}

void BaseMonster::AngerIdleUpdate(float _Delta)
{
	static float AngerIdleTimer = 0.0f;

	if (AngerIdleTimer > 1.0f)
	{
		AngerIdleTimer = 0.0f;
		ChangeState(MonsterState::AngerMove);
		return;
	}

	AngerIdleTimer += _Delta;
}

void BaseMonster::AngerMoveStart()
{
	ChangeAnimationState("AngerMove");
}

void BaseMonster::AngerMoveUpdate(float _Delta)
{
	static float MoveTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (Dir == ActorDir::Down)
	{
		MovePos = { 0.0f, Speed * _Delta };
		CheckPos = BOTPOS;
	}

	if (Dir == ActorDir::Up)
	{
		MovePos = { 0.0f, -Speed * _Delta };
		CheckPos = TOPPOS;
	}

	if (Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTPOS;
	}

	if (Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = RIGHTPOS;
	}

	CheckPos += GetPos();

	bool CheckTile = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos, _Delta);

	if (false == CheckTile)
	{
		AddPos(MovePos);
	}

	else if (true == CheckTile)
	{
		RandomDir("AngerMove");
	}

	MoveTimer += _Delta;
}

void BaseMonster::DieStart()
{
	ChangeAnimationState("Die");
}

void BaseMonster::DieUpdate(float _Delta)
{
	ChangeState(MonsterState::Die);
}

void BaseMonster::RandomDir(const std::string& _StateName)
{
	int Random = GameEngineRandom::MainRandom.RandomInt(1, 4);

	ActorDir CurDir = Dir;
	ActorDir NextDir = Dir;

	switch (Random)
	{
	case 1:
		NextDir = ActorDir::Down;
		break;
	case 2:
		NextDir = ActorDir::Up;
		break;
	case 3:
		NextDir = ActorDir::Left;
		break;
	case 4:
		NextDir = ActorDir::Right;
		break;
	default:
		break;
	}

	if (CurDir != NextDir)
	{
		Dir = NextDir;
		ChangeAnimationState(_StateName);
	}
}

void BaseMonster::ChangeAnimationState(const std::string& _StateName) 
{

}