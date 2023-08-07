#pragma once
#include "ContentLevel.h"
#include <vector>
#include <list>

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

	bool CheckTile(const float4& _Pos, float _Delta);
	bool CheckSidePos(const float4& _Pos);
	void MoveTile(GameEngineRenderer* _Renderer,int _X, int _Y);
	void SetBubble(const float4& _Pos, int _BubblePower);
	void BubblePop(const int _X, const int _Y);
	void SideBubblePop(const int _X, const int _Y, const std::string& _SpriteName, const std::string& _AnimationName, float _Inter = 0.1f);
	void PopTile(const int _X, const int _Y);
	void TileChange(const int _X, const int _Y, const std::string& _SpriteName, const std::string& _AnimationName, float _Inter = 0.1f);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void MapFileLoad(const std::string& _FileName);
	void TileSetting();

	std::vector<std::vector<class GameMapInfo>> TileInfo;
	class TileMap* GroundTile = nullptr;
	class TileMap* ObjectTile = nullptr;

	std::list<class GameMapIndex> AllBubbleIndex;
	std::list<class GameMapIndex> AllBubbleDeathIndex;

private:
	float LerpTime = 1.0f;

	BaseCharacter* Player = nullptr;
	class PlayTimer* PlayTimerPtr = nullptr;
};

