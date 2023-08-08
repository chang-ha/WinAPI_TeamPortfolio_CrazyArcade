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


	// UI
	int CurrentStage = -1;

	void CreateGameStartAnimation();
	void CreateUIElements();

private:
	void setGameStartCallBack();

	void SetUpUIStart();

	void SetUpStageInfo();
	class CommonTexture* m_StageInfo = nullptr;
	const float4 CONST_StageInfoStartPos = float4{ 12.0f , 2.0f };

	void SetUpFadeScreen();
	class FadeScreen* m_FadeScreen = nullptr;



	void SetUpTimer();
	class PlayTimer* PlayTimerPtr = nullptr;

	const float4 CONST_TimerLocation = float4{ 711.0f , 78.0f };
	const float CONST_TimeSetting = 120.0f;

	void SetUpCharacterStatePanel();


	void SetGoBackButton();
	class Button* m_GoBackButton = nullptr;

	void SetUpUIEnd();



private:
	float LerpTime = 1.0f;

	BaseCharacter* Player = nullptr;
};

