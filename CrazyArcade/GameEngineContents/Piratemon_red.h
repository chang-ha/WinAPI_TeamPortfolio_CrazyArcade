#pragma once
#include "BaseMonster.h"

class Piratemon_red : public BaseMonster
{
public:
	// constrcuter destructer
	Piratemon_red();
	~Piratemon_red();

	// delete Function
	Piratemon_red(const Piratemon_red& _Other) = delete;
	Piratemon_red(Piratemon_red&& _Other) noexcept = delete;
	Piratemon_red& operator=(const Piratemon_red& _Other) = delete;
	Piratemon_red& operator=(Piratemon_red&& _Other) noexcept = delete;

protected:
	void ChangeAnimationState(const std::string& _StateName) override;
	class PlayLevel* CurPlayLevel = nullptr;
	class TileMap* CurTile = nullptr;

	TileObjectOrder CurTileType = TileObjectOrder::Empty;

private:
	void Start() override;
	void Update(float _Delta) override;

	void MoveUpdate(float _Delta) override;

	float4 ShadowPos = { 0.0f, 30.0f };
};

