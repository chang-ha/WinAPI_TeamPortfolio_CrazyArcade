#pragma once
#include "ContentLevel.h"
#include <vector>


enum class TitleButtonActor
{
	GameStart,
	MapEditor,
	Max,
};


class TitleLevel : public ContentLevel
{
public:
	// constructer destructer
	TitleLevel();
	~TitleLevel();

	// delete function
	TitleLevel(const TitleLevel& _Ohter) = delete;
	TitleLevel(TitleLevel&& _Ohter) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	void CreateTitleUI();
	void InitTitleButton();
	std::vector<class Button*> vecTitleButton;

	void setupTitleGameStartButton();
	const float4 CONST_GameStartButtonStartPos = float4{ 291.0f , 400.0f };
	void CallBackGameStartButtonFunc();

	void setupTitleMapEditorButton();
	const float4 CONST_MapEditorButtonStartPos = float4{ 291.0f , 500.0f };
	void CallBackMapEditorButtonFunc();

};

