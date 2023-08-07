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

