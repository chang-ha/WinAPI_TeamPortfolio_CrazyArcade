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

	float4 GetCharacterPos()
	{
		CharacterPos = { PosX, PosY };
		return CharacterPos;
	}

protected:
	virtual void CreateSprite(
		const std::string& _TextureName,
		int _XCount,
		int _YCount = 1
	);

	void StateUpdate(float _Delta);
	void ChangeState(CharacterState _State);
	virtual void ChangeAnimationState(const std::string& _StateName);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	CharacterState State = CharacterState::Max;
	std::string CurState = "";
	GameEngineRenderer* MainRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void SwitchDebugData()
	{
		IsDebugData = !IsDebugData;
	}

	void CharacterPosToIndex();

protected:
	ActorDir Dir = ActorDir::Down;
	float Speed = 300.0f;

	void DirCheck();

private:
	bool IsDebugData = false;

	float PosX = 0.0f;
	float PosY = 0.0f;

	float4 CharacterPos = { 0, 0 };

};

