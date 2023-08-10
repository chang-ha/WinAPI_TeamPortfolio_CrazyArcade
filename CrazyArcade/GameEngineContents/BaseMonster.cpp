#include "BaseMonster.h"

BaseMonster::BaseMonster()
{
}

BaseMonster::~BaseMonster()
{
}

void BaseMonster::Update(float _Delta)
{
	StateUpdate(_Delta);
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
	//case MonsterState::BreakOut:
	//	break;
	//case MonsterState::Ice:
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
	//case MonsterState::BreakOut:
	//	break;
	//case MonsterState::Ice:
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

	// ObjectTile에 닿으면 방향 전환

}


void BaseMonster::DirCheck()
{

}

void BaseMonster::ChangeAnimationState(const std::string& _StateName) 
{

}