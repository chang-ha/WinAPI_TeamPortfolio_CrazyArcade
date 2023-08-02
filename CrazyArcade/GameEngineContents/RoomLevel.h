#pragma once
#include "ContentLevel.h"

#include <vector>


enum class ButtonActor
{
	MapSelect,
	GameStart,
	Max,
};

enum class WindowPanelActor
{
	MapSelect,

	Max,
};



class Button;
class WindowPanelUI;
class RoomLevel : public ContentLevel
{
public:
	// constructer destructer
	RoomLevel();
	~RoomLevel();

	// delete function
	RoomLevel(const RoomLevel& _Ohter) = delete;
	RoomLevel(RoomLevel&& _Ohter) noexcept = delete;
	RoomLevel& operator=(const RoomLevel& _Other) = delete;
	RoomLevel& operator=(RoomLevel&& _Other) noexcept = delete;



protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// GameEngineLevel 상속
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


	// this
	void loadWindowElement();
	std::vector<WindowPanelUI*> vecWindowPanel;

	void loadButtonElement();
	std::vector<Button*> vecButton;

	void loadCharacterButton();
	void loadCharacterTraits();
	std::vector<Button*> vecCharacterButton;

	const float4 m_CharacterButtonStartPos = float4{ 489.0f , 83.0f };
	const float4 m_SpacingBTWCharacterButton = float4{ 7.0f, 4.0f };

	const float4 m_CharacterTraitsStartPos = float4{ 276.0f , 56.0f };


	void updateButtonVisibility();

	bool m_ButtonUpdateValue = true;

	void clickSelectButton();


};

