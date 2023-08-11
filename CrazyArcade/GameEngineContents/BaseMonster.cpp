#include "BaseMonster.h"
#include "GlobalUtils.h"
#include "PlayLevel.h"

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
		 // Die
	}

	//if (CurTileType == TileObjectOrder::Structure
	//	|| CurTileType == TileObjectOrder::MovableBlock
	//	|| CurTileType == TileObjectOrder::ImmovableBlock)
	//{
	//	// DirChange
	//}

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
	//case MonsterState::Ready:
	//	break;
	//case MonsterState::Freeze:
	//	break;
	//case MonsterState::Melt:
	//	break;
	//case MonsterState::Anger:
	//	break;
	//case MonsterState::Die:
	//	break;
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
	//case MonsterState::Ready:
	//	break;
	//case MonsterState::Freeze:
	//	break;
	//case MonsterState::Melt:
	//	break;
	//case MonsterState::Anger:
	//	break;
	//case MonsterState::Die:
	//	break;
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

	TileObjectOrder TileType = PlayLevel::CurPlayLevel->GetCurTileType(GetPos());

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

	MoveTimer += _Delta;
}


void BaseMonster::DirCheck()
{
	ActorDir CheckDir = Dir;
	bool IsDirCheck[4] = { true, true, true, true };

	TileObjectOrder TileType = PlayLevel::CurPlayLevel->GetCurTileType(GetPos());

	switch (Dir)
	{
	case ActorDir::Left:
		break;
	case ActorDir::Right:
		break;
	case ActorDir::Up:
		break;
	case ActorDir::Down:
		break;
	default:
		break;
	}
}

void BaseMonster::ChangeAnimationState(const std::string& _StateName) 
{

}