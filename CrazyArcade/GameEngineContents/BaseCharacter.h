#pragma once

#include "ActorEnum.h"

#include <string>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class BaseCharacter : public GameEngineActor
{
public:
	// constrcuter destructer
	BaseCharacter();
	~BaseCharacter();

	// delete Function
	BaseCharacter(const BaseCharacter& _Other) = delete;
	BaseCharacter(BaseCharacter&& _Other) noexcept = delete;
	BaseCharacter& operator=(const BaseCharacter& _Other) = delete;
	BaseCharacter& operator=(BaseCharacter&& _Other) noexcept = delete;

protected:
	void DirCheck();
	void StateUpdate(float _Delta);
	void ChangeState(CharacterState _State);
	void ChangeAnimationState(const std::string& _StateName);

	void WaitStart();

	void WaitUpdate(float _Delta);

	ActorDir Dir = ActorDir::Down;
	CharacterState State = CharacterState::Max;
	std::string CurState = "";
private:
	GameEngineRenderer* MainRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
};

