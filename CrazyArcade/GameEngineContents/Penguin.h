#pragma once

#include "BaseMonster.h"

// Ό³Έν :
class Penguin : public BaseMonster
{
public:
	// constrcuter destructer
	Penguin();
	~Penguin();

	// delete Function
	Penguin(const Penguin& _Other) = delete;
	Penguin(Penguin&& _Other) noexcept = delete;
	Penguin& operator=(const Penguin& _Other) = delete;
	Penguin& operator=(Penguin&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};

