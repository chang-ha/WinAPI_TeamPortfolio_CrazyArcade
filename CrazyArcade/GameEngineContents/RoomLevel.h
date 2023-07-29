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
	
	
	
	void updateButtonVisibility();

	bool ButtonUpdateValue = true;
	
	void clickSelectButton();


};

