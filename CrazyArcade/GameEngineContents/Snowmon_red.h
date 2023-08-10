#pragma once
#include "BaseMonster.h"

// Ό³Έν :
class Snowmon_red : public BaseMonster
{
public:
	// constrcuter destructer
	Snowmon_red();
	~Snowmon_red();

	// delete Function
	Snowmon_red(const Snowmon_red& _Other) = delete;
	Snowmon_red(Snowmon_red&& _Other) noexcept = delete;
	Snowmon_red& operator=(const Snowmon_red& _Other) = delete;
	Snowmon_red& operator=(Snowmon_red&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};

