#pragma once
#include "ContentLevel.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineSound.h>
#include <vector>
#include <list>

enum class PlayState
{
	Single,
	Multi
};

struct CharacterStatus
{
public:
	bool AliveState = true;
};

struct PlayerResult
{
public:
	int KillNUmber = 0;
	int SaveNUmber = 0;
	bool PlayerWinValue = false;
};

class BaseCharacter;
enum class PlayerNum;
class PlayLevel : public ContentLevel
{
	friend class Penguin;
	friend class BaseMonster;
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

	bool CheckTile(const float4& _Pos, float _Delta, const PlayerNum& _PlayerNum);
	bool CheckSidePos(const float4& _Pos, const PlayerNum& _PlayerNum);
	void MoveTile(GameEngineRenderer* _Renderer,int _X, int _Y, const PlayerNum& _PlayerNum);
	void SetBubble(const float4& _Pos, int _BubblePower, const PlayerNum& _PlayerNum);
	void BubblePop(const int _X, const int _Y);
	void PrevBubblePop(const int _X, const int _Y);
	void SideBubblePop(const int _X, const int _Y, const std::string& _SpriteName, const std::string& _AnimationName, float _Inter = 0.1f);
	void PopTile(const int _X, const int _Y);
	void TileChange(const int _X, const int _Y, const std::string& _SpriteName, const std::string& _AnimationName, float _Inter = 0.1f);
	enum class TileObjectOrder GetCurTileType(const float4& _Pos);
	class GameMapIndex GetCurIndex(const float4& _Pos);
	bool MonsterCheckTile(const float4& _Pos, float _Delta);
	
	template <typename MonsterType>
	MonsterType* CreateMonster()
	{
		MonsterType* NewMonster = CreateActor<MonsterType>(UpdateOrder::Monster);

		if (nullptr != NewMonster)
		{
			StageMonsters.push_back(NewMonster);
			return NewMonster;
		}
		else
		{
			MsgBoxAssert("몬스터 생성에 실패했습니다");
			return nullptr;
		}
	}

	int GetStageMonsterCount() const
	{
		return static_cast<int>(StageMonsters.size());
	}

	void CheckItemInTile(int _X, int _Y);
	void CheckItemInTile(float _X, float _Y);

	class TileMap* GetGroundTile()
	{
		return GroundTile;
	}

	class TileMap* GetObjectTile()
	{
		return ObjectTile;
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void MapFileLoad(const std::string& _FileName);
	void TileSetting();

	// Player
	BaseCharacter* Player = nullptr;
	BaseCharacter* Player2 = nullptr;
	PlayState LevelPlayState;
	void CharacterSetting();

	// Monster
	std::list<BaseMonster*> StageMonsters;
	void StageMonstersDeath();
	void MonsterListDelete();
	
	// Item
	void ItemSetting();
	void ItemRelease();
	void CreateItemInBlock(int _X, int _Y);
	void CreateItemInTile(int _X, int _Y, ItemType _Type);

	bool ItemDebugValue = false;

	std::vector<std::vector<class Item*>> Items;
	class Item* ItemActor = nullptr;

	// Tile
	std::vector<std::vector<class GameMapInfo>> TileInfo;
	class TileMap* GroundTile = nullptr;
	class TileMap* ObjectTile = nullptr;

	// Bubble
	std::list<class GameMapBubble> AllBubbleIndex;
	std::list<class GameMapIndex> AllBubbleDeathIndex;

	// 각 플레이어별 몬스터를 죽인 횟수, 아군을 구한 횟수, 승패 판정을 아래의 벡터에 넣어주세요
	// 벡터 생성은 UI에서 했습니다.
	// 배열의 순서는 플레이어 오름차순으로 입니다.
	std::vector<PlayerResult> VecPlayerResult;

	// UI
	int CurrentStage = -1;
	std::string NextLevelName = "";

	void SoketRelease();
	std::vector<class ItemSoket*> Sokets;

	void CreateUIElements();
	
	// 보스 맵 패턴
	void BubblePattern(const int BossIndex_X, const int BossIndex_Y, const int _Range);

	// Sound
	void BubblePopPlay();
	bool PlayBubblePopEffectSound = false;

private:
	void UILevelStart();

	void CreateBossImage();
	void CreateGameStartPlayerSignal();

	void CreateGameStartAnimation();
	class GameStartAnimation* m_GameStartAnimation = nullptr;
	void OnGameStartAnimation();
	void setGameStartCallBack();
	bool GameStartCheckValue = false;

	void CreatePortrait();
	std::vector<class PlayPortrait*> vec_PlayPortrait;
	const float4 CONST_PlayPortraitStartPos = float4{ 654.0f , 98.0f };
	const float4 CONST_PlayPortraitNextPos = float4{ 0.0f , 43.0f };


	void UILevelEnd();
	void ReleaseLevelComposition();
	void ReleaseResultWindow();

	void SetUpUIStart();

	void SetUpStageInfo();
	class CommonTexture* m_StageInfo = nullptr;
	const float4 CONST_StageInfoStartPos = float4{ 12.0f , 2.0f };

	void SetUpFadeScreen();
	class FadeScreen* m_FadeScreen = nullptr;

	void SetUpTimer();
	class PlayTimer* m_PlayTimer = nullptr;
	const float4 CONST_TimerLocation = float4{ 711.0f , 78.0f };
	const float CONST_TimeSetting = 120.0f;


	void SetGoBackButton();
	class Button* m_GoBackButton = nullptr;
	const float4 CONST_GoBackButtonStartPos = float4{ 647.0f , 561.0f };
	void clickGoBackButton();

	void CreateGameResult();

	void SetUpResultWindow();
	class PlayResultWindow* m_ResultWindow = nullptr;
	const float4 CONST_ResultWindowStartPos = float4{ 39.0f , 138.0f };

	void SetUpResultBoardAnimation();
private:
	void updateGameOverResult(float _Delta);
	void updateVictoryRoll();
	bool detectAllMonsterKill();

	void updateCharacterPortrait();
	std::vector<CharacterStatus> vecCharacterState;

private:
	bool GameOverCheckValue = false;
	bool WinCheckValue = false;

	float GameOverTime = 0.0f;
	const float GameOverDuration = 10.0f;

	void StartGameOver();

private:
	bool PatternAnimationEnd = true;
	bool All_Null = true;

	class TileMap* BossBubbleTile = nullptr;
	void ClearBossPattern();

private:
	float LerpTime = 1.0f;
};