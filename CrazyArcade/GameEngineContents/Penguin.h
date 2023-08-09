#pragma once

#include "BaseMonster.h"

// Ό³Έν :
class Penguin : public BaseMonster
{
public:
	// constrcuter destructer
	Penguin();
	~Penguin();

	// delete Function
	Penguin(const Penguin& _Other) = delete;
	Penguin(Penguin&& _Other) noexcept = delete;
	Penguin& operator=(const Penguin& _Other) = delete;
	Penguin& operator=(Penguin&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// Before Virtual
	void StateUpdate(float _Delta);
	void ChangeState(MonsterState _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void HittenStart();
	void HittenUpdate(float _Delta);
};

