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
	//case MonsterState::None:
	//	break;
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	//case MonsterState::Move:
	//	break;
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
	//case MonsterState::None:
	//	break;
	case MonsterState::Idle:
		IdleStart();
		break;
	//case MonsterState::Move:
	//	break;
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

}

void BaseMonster::IdleUpdate(float _Delta)
{

}

void BaseMonster::MoveStart()
{

}

void BaseMonster::MoveUpdate(float _Delta)
{

}


void BaseMonster::DirCheck()
{

}