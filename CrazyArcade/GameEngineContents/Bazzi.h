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
	int MinSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MinSpeed;
	int MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MaxSpeed;
	int Speed = MinSpeed;

	int MinBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MinBombPower;
	int MaxBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MaxBombPower;
	int BombPower = MinBombPower;

	int MinBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MinWaterBombs;
	int MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Bazzi)].MaxWaterBombs;
	int BombCount = MinBombCount;

	void Start() override;
};