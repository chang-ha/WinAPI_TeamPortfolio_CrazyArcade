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

	int GetBubblePower() override
	{
		return BubblePower;
	}

	float GetSpeed() override
	{
		return Speed;
	}

private:
	float Speed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MinSpeed * SPEEDREFERENCEVALUE;
	float MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MaxSpeed * SPEEDREFERENCEVALUE;
	int BubblePower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MinBombPower;
	int MaxBubblePower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MaxBombPower;
	int BombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MinWaterBombs;
	int MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MaxWaterBombs;

	void Start() override;
};