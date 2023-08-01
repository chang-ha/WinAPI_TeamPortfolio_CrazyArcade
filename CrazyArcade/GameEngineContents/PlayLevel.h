#pragma once
#include "ContentLevel.h"
#include <vector>

class BaseCharacter;
class PlayLevel : public ContentLevel
{
public:
	static PlayLevel* CurPlayLevel;

	// constructer destructer
	PlayLevel();
	~PlayLevel();

	// delete function
	PlayLevel(const PlayLevel& _Ohter) = delete;
	PlayLevel(PlayLevel&& _Ohter) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

	bool CheckTile(const float4& _Pos);
	void MoveTile(GameEngineRenderer* _Renderer,int _X, int _Y);
	void SetBubble(const float4& _Pos);
	void BubbleReset(const int _X, const int _Y);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void TileSetting();

	std::vector<std::vector<class GameMapInfo>> TileInfo;
	class TileMap* GroundTile = nullptr;
	class TileMap* ObjectTile = nullptr;

	std::vector<class GameMapIndex> AllBubbleIndex;
	std::vector<class GameMapIndex> AllBubbleDeathIndex;

private:
	BaseCharacter* Player = nullptr;

	class PlayTimer* PlayTimerPtr = nullptr;
};

