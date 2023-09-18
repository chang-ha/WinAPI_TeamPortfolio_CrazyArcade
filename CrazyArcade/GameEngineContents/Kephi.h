#pragma once

#include "BaseCharacter.h"

class Kephi : public BaseCharacter
{
public:
	// constrcuter destructer
	Kephi();
	~Kephi();

	// delete Function
	Kephi(const Kephi& _Other) = delete;
	Kephi(Kephi&& _Other) noexcept = delete;
	Kephi& operator=(const Kephi& _Other) = delete;
	Kephi& operator=(Kephi&& _Other) noexcept = delete;

protected:
	void ChangeAnimationState(const std::string& _StateName) override;

private:
	void Start() override;
};