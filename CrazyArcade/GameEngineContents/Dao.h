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
		return BubblePower + 1;
	}

	float GetSpeed() override
	{
		return Speed;
	}

private:
	float Speed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MinSpeed * SPEEDREFERENCEVALUE;
	float MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MaxSpeed * SPEEDREFERENCEVALUE;
	int BubblePower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MinBombPower;
	int MaxBubblePower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MaxBombPower;
	int BombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MinWaterBombs;
	int MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MaxWaterBombs;

	void Start() override;
};