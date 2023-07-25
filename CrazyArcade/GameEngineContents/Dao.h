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
	void CreateSprite(const std::string& _TextureName, int _XCount, int _YCount = 1) override;
	void ChangeAnimationState(const std::string& _StateName) override;

private:
	float Speed = 300.0f;

	void Start() override;
	void Update(float _Delta) override;
};