#pragma once
#include "ContentLevel.h"
#include <vector>

class PlayLevel : public ContentLevel
{
public:
	// constructer destructer
	PlayLevel();
	~PlayLevel();

	// delete function
	PlayLevel(const PlayLevel& _Ohter) = delete;
	PlayLevel(PlayLevel&& _Ohter) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	const float4 Tile_StartPos = { 20, 41 };

private:
	class TileMap* Tile = nullptr;
	std::vector<std::vector<class GameMapInfo>> TileInfo;
	//class TileMap* Structure = nullptr;
	//class TileMap* Block = nullptr;
	class GameEngineRenderer* TileRenderer = nullptr;
};

