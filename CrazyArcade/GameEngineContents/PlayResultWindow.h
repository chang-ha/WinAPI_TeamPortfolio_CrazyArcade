#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include "PlayLevel.h"
#include <vector>


// 설명 :
class PlayResultWindow : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayResultWindow();
	~PlayResultWindow();

	// delete Function
	PlayResultWindow(const PlayResultWindow& _Other) = delete;
	PlayResultWindow(PlayResultWindow&& _Other) noexcept = delete;
	PlayResultWindow& operator=(const PlayResultWindow& _Other) = delete;
	PlayResultWindow& operator=(PlayResultWindow&& _Other) noexcept = delete;


	void initResultWindow();

	void OnResultWindow(const std::vector<PlayerResult>& _VecResult);

	void ActorRelease();


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	// this
	int m_ActiveRoomCount = 0;

	void setupFadeWindow();
	class CommonTexture* m_ResultFadeWindow = nullptr;
	const unsigned char CONST_FadeWindowAlpha = 150;

	void setupResultSummary();
	class CommonTexture* m_ResultSummary = nullptr;
	const float4 CONST_ResultSummaryStartPos = float4{ 109.0f , 14.0f };


	void setupResultLine();
	std::vector<class PlayResultLine*> vecPlayResultLine;
	const float4 CONST_ResultLineStartPos = float4{ 14.0f , 42.0f };
	const float4 CONST_ResultLineNextPos = float4{ 0.0f , 25.0f };
};

