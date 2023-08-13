#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <vector>


enum class ExpState 
{
	ExpUI,
	ExpAcquisition,
	Max,
};


// 설명 :
class PlayResultLine : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayResultLine();
	~PlayResultLine();

	// delete Function
	PlayResultLine(const PlayResultLine& _Other) = delete;
	PlayResultLine(PlayResultLine&& _Other) noexcept = delete;
	PlayResultLine& operator=(const PlayResultLine& _Other) = delete;
	PlayResultLine& operator=(PlayResultLine&& _Other) noexcept = delete;

	void initResultLine(const int _LineNumber);

	void changePlayerMatchValue(const bool _Win);
	void changePlayerLevel(const int _PlayerLevel);
	void changeKillNumber(const int _KillNumber);
	void changeSaveNumber(const int _KillNumber);

	void ActorRelease();

	void onResultLine();


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;

	void LevelEnd() override;

	// this
	int m_LineNumber = 0;

	bool m_ShowLineValue = false;

	struct ResultLineInfo
	{
	public:
		class CommonTexture* Back = nullptr;
		class CommonTexture* LineNumber = nullptr;
		class CommonTexture* PlayerWinOrLose = nullptr;
		class CommonTexture* PlayerRank = nullptr;
		class CommonTexture* PlayerID = nullptr;
		std::vector<class CommonTexture*> KillNumber;
		std::vector<class CommonTexture*> SaveNumber;
		class ExpAcquisition* ExpAcquisition = nullptr;
		class ExpUI* ExpUI = nullptr;
		class CommonTexture* LevelUp = nullptr;
	};

	ResultLineInfo ResultLine;

	void setupLineBack();

	void setupLineNubmer();
	const float4 CONST_LineNumberStartPos = float4{ 10.0f , 5.0f };

	void setupWinOrLose();
	bool m_GameMatchWinValue = false;
	const int CONST_WinEXPIncreaseAmount = 80;
	const float4 CONST_PlayerWinOrLoseStartPos = float4{ 25.0f , 3.0f };

	void setupLineRank();
	int PlayerLevel = 0;
	int m_Rank = 0;
	const float4 CONST_PlayerRankStartPos = float4{ 98.0f , 4.0f };

	void setupPlayerID();
	const float4 CONST_PlayerIDStartPos = float4{ 116.0f , 4.0f };

	void setupKillNumber();
	int m_KillNumberSlot = 2;
	int m_killNumber = 0;
	const int CONST_KillEXPAmount = 10;
	const float4 CONST_KillNumberStartPos = float4{ 196.0f , 5.0f };

	void setupSaveNumber();
	int m_SaveNumberSlot = 2;
	int m_SaveNumber = 0;
	const int CONST_SaveEXPAmount = 50;
	const float4 CONST_SaveNumberStartPos = float4{ 238.0f , 5.0f };

	void setupExp();
	const float4 CONST_ExpPanelStartPos = float4{ 332.0f , 3.0f };

	void setupLevelUp();
	const float4 CONST_LevelUpStartPos = float4{ 397.0f , 2.0f };


	void updateEXP();
	bool m_updateExpCheckValue = false;
	int m_ExpIncreaseValue = 0;
	bool m_ExpUpdateCheckValue = false;

	void updateRank();
	bool m_RankUpdateValue = false;

	void updateState(float _Delta);
	ExpState m_State = ExpState::Max;
	float StateTime = 0.0f;
	const float CONST_EachStateDuration = 2.0f;

	void changeState(ExpState _State);

	void startExpUI();
	void updateExpUI(float _Delta);

	void startExpAcquisition();
	void updateExpAcquisition(float _Delta);
};

