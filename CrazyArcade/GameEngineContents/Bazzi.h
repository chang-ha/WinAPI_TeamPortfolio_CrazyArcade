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
	void CreateSprite(const std::string& _TextureName, int _XCount, int _YCount = 1) override;
	void ChangeAnimationState(const std::string& _StateName) override;

private:
	float Speed = 300.0f;

	void Start() override;
	void Update(float _Delta) override;
};