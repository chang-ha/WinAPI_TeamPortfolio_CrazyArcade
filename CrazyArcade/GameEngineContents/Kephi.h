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
	int MinSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MinSpeed;
	int MaxSpeed = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MaxSpeed;
	int Speed = MinSpeed;

	int MinBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MinBombPower;
	int MaxBombPower = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MaxBombPower;
	int BombPower = MinBombPower;

	int MinBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MinWaterBombs;
	int MaxBombCount = GlobalValue::VecCharacterTraits[static_cast<int>(CharacterList::Kephi)].MaxWaterBombs;
	int BombCount = MinBombCount;

	void Start() override;
};