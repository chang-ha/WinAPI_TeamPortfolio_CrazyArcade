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
	float Speed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MinSpeed * SPEEDREFERENCEVALUE;
	float MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MaxSpeed * SPEEDREFERENCEVALUE;
	int BubblePower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MinBombPower;
	int MaxBubblePower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MaxBombPower;
	int BombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MinWaterBombs;
	int MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MaxWaterBombs;

	void Start() override;
};