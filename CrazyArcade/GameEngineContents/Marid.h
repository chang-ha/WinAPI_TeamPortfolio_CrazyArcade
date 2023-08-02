#pragma once

#include "BaseCharacter.h"

class Marid : public BaseCharacter
{
public:
	// constrcuter destructer
	Marid();
	~Marid();

	// delete Function
	Marid(const Marid& _Other) = delete;
	Marid(Marid&& _Other) noexcept = delete;
	Marid& operator=(const Marid& _Other) = delete;
	Marid& operator=(Marid&& _Other) noexcept = delete;

protected:
	void ChangeAnimationState(const std::string& _StateName) override;

private:
	float Speed = 300.0f;

	void Start() override;
};