#pragma once
#define BOSSMOVERANGE GlobalValue::MapTileSize.X
#define BOSSMOVESPEED GlobalValue::MapTileSize.X * 2

#include "BaseMonster.h"

// ���� :
class TileMap;
class PlayLevel;
class Penguin : public BaseMonster
{
	friend PlayLevel;
public:
	// constrcuter destructer
	Penguin();
	~Penguin();

	// delete Function
	Penguin(const Penguin& _Other) = delete;
	Penguin(Penguin&& _Other) noexcept = delete;
	Penguin& operator=(const Penguin& _Other) = delete;
	Penguin& operator=(Penguin&& _Other) noexcept = delete;

	const std::vector<std::vector<float4>> GetBossTile()
	{
		return BossTile;
	}

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

	void MoveStart();
	void MoveUpdate(float _Delta);

	void DieReadyStart();
	void DieReadyUpdate(float _Delta);

	void DieBubbleStart();
	void DieBubbleUpdate(float _Delta);

	void DieStart();
	void DieUpdate(float _Delta);

	void HitJudgement();
	void HittenStart();
	void HittenUpdate(float _Delta);

	void SummonStart();
	void SummonUpdate(float _Delta);

	void PatternUpdate();

	bool IsDebugMode = false;
	bool IsHitten = false;
	bool PatternStart = false;
	int BossHP = 2;
	float4 MoveRange = float4::ZERO;
	float4 MoveSpeed = float4::ZERO;
	int PatternCount = 0;
	float PatternTimer = 0.0f;
	float DieAlpha = 255.0f;
	std::vector<std::vector<float4>> BossTile;
};

