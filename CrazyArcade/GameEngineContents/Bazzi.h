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

	float GetSpeed() override
	{
		return Speed;
	}

	int GetBubblePower() override
	{
		return BubblePower;
	}

	int GetBombCount() override
	{
		return BombCount;
	}

	void BombCountPlus() override
	{
		++BombCount;
	}

	void BombCountMinus() override
	{
		--BombCount;
	}

private:
	float Speed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MinSpeed * SPEEDREFERENCEVALUE;
	float MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MaxSpeed * SPEEDREFERENCEVALUE;
	int BubblePower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MinBombPower;
	int MaxBubblePower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MaxBombPower;
	int BombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MinWaterBombs;
	int MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MaxWaterBombs;

	void Start() override;
};