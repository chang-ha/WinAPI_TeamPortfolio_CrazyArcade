#pragma once

#include "BaseMonster.h"

// Ό³Έν :
class TileMap;
class PlayLevel;
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
	TileMap* CurLevelTile = nullptr;
	PlayLevel* CurPlayLevel = nullptr;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void StateUpdate(float _Delta) override;
	void ChangeState(MonsterState _State) override;

	void IdleStart();
	void IdleUpdate(float _Delta);

	void HittenStart();
	void HittenUpdate(float _Delta);
};

