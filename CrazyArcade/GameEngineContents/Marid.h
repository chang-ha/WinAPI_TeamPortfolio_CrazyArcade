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
	int MinSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MinSpeed;
	int MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MaxSpeed;
	int Speed = MinSpeed;

	int MinBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MinBombPower;
	int MaxBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MaxBombPower;
	int BombPower = MinBombPower;

	int MinBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MinWaterBombs;
	int MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Marid)].MaxWaterBombs;
	int BombCount = MinBombCount;

	void Start() override;
};