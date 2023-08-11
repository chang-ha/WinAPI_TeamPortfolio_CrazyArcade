#pragma once

#include "BaseMonster.h"

// Ό³Έν :
class Snowmon_black : public BaseMonster
{
public:
	// constrcuter destructer
	Snowmon_black();
	~Snowmon_black();

	// delete Function
	Snowmon_black(const Snowmon_black& _Other) = delete;
	Snowmon_black(Snowmon_black&& _Other) noexcept = delete;
	Snowmon_black& operator=(const Snowmon_black& _Other) = delete;
	Snowmon_black& operator=(Snowmon_black&& _Other) noexcept = delete;

protected:
	void ChangeAnimationState(const std::string& _StateName) override;

	class PlayLevel* CurPlayLevel = nullptr;
	class TileMap* CurTile = nullptr;

	TileObjectOrder CurTileType = TileObjectOrder::Empty;

private:
	void Start() override;
};

