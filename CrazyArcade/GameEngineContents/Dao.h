#pragma once

#include "BaseCharacter.h"

class Dao : public BaseCharacter
{
public:
	// constrcuter destructer
	Dao();
	~Dao();

	// delete Function
	Dao(const Dao& _Other) = delete;
	Dao(Dao&& _Other) noexcept = delete;
	Dao& operator=(const Dao& _Other) = delete;
	Dao& operator=(Dao&& _Other) noexcept = delete;

protected:
	void ChangeAnimationState(const std::string& _StateName) override;

	int GetBubblePower() override
	{
		return BubblePower;
	}

private:
	float Speed = 300.0f;
	int BubblePower = 1;

	void Start() override;
};