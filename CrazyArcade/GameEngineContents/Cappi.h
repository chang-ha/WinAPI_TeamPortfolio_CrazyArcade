#pragma once

#include "BaseCharacter.h"

class Cappi : public BaseCharacter
{
public:
	// constrcuter destructer
	Cappi();
	~Cappi();

	// delete Function
	Cappi(const Cappi& _Other) = delete;
	Cappi(Cappi&& _Other) noexcept = delete;
	Cappi& operator=(const Cappi& _Other) = delete;
	Cappi& operator=(Cappi&& _Other) noexcept = delete;

protected:
	void ChangeAnimationState(const std::string& _StateName) override;

private:
	float Speed = 300.0f;

	void Start() override;
};

