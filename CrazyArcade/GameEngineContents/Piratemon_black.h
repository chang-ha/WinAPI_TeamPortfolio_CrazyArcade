#pragma once
#include "BaseMonster.h"

class Piratemon_black : public BaseMonster
{
public:
	// constrcuter destructer
	Piratemon_black();
	~Piratemon_black();

	// delete Function
	Piratemon_black(const Piratemon_black& _Other) = delete;
	Piratemon_black(Piratemon_black&& _Other) noexcept = delete;
	Piratemon_black& operator=(const Piratemon_black& _Other) = delete;
	Piratemon_black& operator=(Piratemon_black&& _Other) noexcept = delete;

protected:
	void ChangeAnimationState(const std::string& _StateName) override;
	class PlayLevel* CurPlayLevel = nullptr;
	class TileMap* CurTile = nullptr;

	TileObjectOrder CurTileType = TileObjectOrder::Empty;

private:
	void Start() override;
	void Update(float _Delta) override;
	float4 ShadowPos = { 0.0f, 30.0f };
};

