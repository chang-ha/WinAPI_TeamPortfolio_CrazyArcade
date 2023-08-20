#pragma once
#define IDLE_ANI_SPEED 0.10f
#define MOVE_ANI_SPEED 0.10f
#define HITTEN_ANI_SPEED 0.15f

#define ANGER_ANI_SPEED 0.15f
#define BUBBLE_ANI_SPEED 0.18f
#define BUBBLEPATTERN_TIME 10.0f
#define SUMMONPATTERN_TIME 1.0f
#define ANGERHP 3
#define HPBARPOS float4{0, -130}
#define BOSSMOVERANGE GlobalValue::MapTileSize.X
#define BOSSMOVESPEED GlobalValue::MapTileSize.X * 2

#define SUMMON_FRAME 10

#include "BaseMonster.h"
 
// ���� :
class TileMap;
class PlayLevel;
class Penguin : public BaseMonster
{
	friend PlayLevel;
public:
	static Penguin* BossMonster;

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

	ActorDir DirDecision(int _MoveRange);
	void ChangeAnimationState(MonsterState _State);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void AngerStart();
	void AngerUpdate(float _Delta);

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
	void SummonMonster();

	void PatternUpdate();
	void SequentialPatternInit(int _StartRange, int _PatternCount, int _PlusRange);
	void SequentialPatternUpdate();

	bool IsDebugMode = false;
	bool IsHitten = false;
	bool BubblePatternStart = false;
	bool SummonPatternStart = false;

	bool SequentialPatternOn = false;
	int BossHP = 7;
	float4 MoveRange = float4::ZERO;
	float4 MoveSpeed = float4::ZERO;

	int StartRange = 0;
	int PlusRange = 0;
	int PatternCount = 0;
	float BubblePatternTimer = 0.0f;
	float SummonPatternTimer = 0.0f;

	float DieAlpha = 255.0f;

	GameEngineRenderer* HP_Renderer = nullptr;
	GameEngineRenderer* Shadow = nullptr;
	std::vector<std::vector<float4>> BossTile;
};

