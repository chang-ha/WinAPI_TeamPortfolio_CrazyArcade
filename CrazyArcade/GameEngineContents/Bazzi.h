#pragma once

#include "BaseCharacter.h"

class Bazzi : public BaseCharacter
{
public:
	// constrcuter destructer
	Bazzi();
	~Bazzi();

	// delete Function
	Bazzi(const Bazzi& _Other) = delete;
	Bazzi(Bazzi&& _Other) noexcept = delete;
	Bazzi& operator=(const Bazzi& _Other) = delete;
	Bazzi& operator=(Bazzi&& _Other) noexcept = delete;

protected:
	void ChangeAnimationState(const std::string& _StateName) override;

private:
	void Start() override;
};