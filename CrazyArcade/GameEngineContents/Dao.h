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

	float GetSpeed() override
	{
		return Speed * SPEEDREFERENCEVALUE;
	}

	int GetBombPower() override
	{
		return BombPower;
	}

	int GetBombCount() override
	{
		return BombCount;
	}

	void BombCountPlus() override
	{
		if (BombCount < MaxBombCount)
		{
			++BombCount;
			return;
		}
		else
		{
			return;
		}
	}

	void BombCountMinus() override
	{
		--BombCount;
	}

	void BombPowerPlus() override
	{
		if (BombPower < MaxBombPower)
		{
			++BombPower;
			return;
		}
		else
		{
			return;
		}
	}

	void ChangeMaxBombPower() override
	{
		BombPower = MaxBombPower;
	}

	void SpeedUp() override
	{
		if (Speed < MaxSpeed)
		{
			++Speed;
			return;
		}
		else
		{
			return;
		}
	}

	void ChangeMaxSpeed() override
	{
		Speed = MaxSpeed;
	}

private:
	int MinSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MinSpeed;
	int MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MaxSpeed;
	int Speed = MinSpeed;

	int MinBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MinBombPower;
	int MaxBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MaxBombPower;
	int BombPower = MinBombPower;

	int MinBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MinWaterBombs;
	int MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Dao)].MaxWaterBombs;
	int BombCount = MinBombCount;

	void Start() override;
};