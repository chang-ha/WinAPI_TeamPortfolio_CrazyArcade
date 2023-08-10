#include "BaseMonster.h"
#include "GlobalUtils.h"
#include "PlayLevel.h"

#include <GameEngineCore/GameEngineRenderer.h>

BaseMonster::BaseMonster()
{
}

BaseMonster::~BaseMonster()
{
}

void BaseMonster::Start() 
{
	GlobalUtils::SpriteFileLoad("Shadow.Bmp", "Resources\\Textures\\Monster\\", 1, 1);

	ShadowRenderer = CreateRenderer("Shadow.bmp", RenderOrder::Shadow);
	ShadowRenderer->SetRenderPos(BOTCHECKPOS);
}

void BaseMonster::Update(float _Delta)
{
	StateUpdate(_Delta);

	CurTile = PlayLevel::CurPlayLevel->GetCurTileType(GetPos());

	if (CurTile == TileObjectOrder::PopRange)
	{
		// Die
	}

	//if (CurTile == TileObjectOrder::Structure
	//	|| CurTile == TileObjectOrder::MovableBlock
	//	|| CurTile == TileObjectOrder::ImmovableBlock)
	//{
	//	// DirChange
	//}
}

void BaseMonster::Render(float _Delta)
{

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

	// 왼쪽 이동
	if (Dir == ActorDir::Down)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTCHECKPOS;
	}

	MoveTimer += _Delta;

	// ObjectTile에 닿으면 방향 전환

}


void BaseMonster::DirCheck()
{
	ActorDir CheckDir = Dir;

	
}

void BaseMonster::ChangeAnimationState(const std::string& _StateName) 
{

}