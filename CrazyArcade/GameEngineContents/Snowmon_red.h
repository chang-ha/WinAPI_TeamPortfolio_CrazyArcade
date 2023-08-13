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
	void ChangeAnimationState(const std::string& _StateName) override;
	class PlayLevel* CurPlayLevel = nullptr;
	class TileMap* CurTile = nullptr;

	TileObjectOrder CurTileType = TileObjectOrder::Empty;

private:
	void Start() override;
	float4 ShadowPos = { 0.0f, 35.0f };
};

