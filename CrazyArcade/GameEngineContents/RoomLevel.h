#pragma once
#include "ContentLevel.h"
#include "ActorEnum.h"

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
	std::vector<Button*> vecCharacterButton;

	const float4 m_CharacterButtonStartPos = float4{ 489.0f , 83.0f };
	const float4 m_SpacingBTWCharacterButton = float4{ 7.0f, 4.0f };

	const float4 m_GameExitButtonStartPos = float4{ 749.0f, 572.0f };

	void clickSelectButton();
	void clickBazziCharacterButton();
	void clickDaoCharacterButton();
	void clickMaridCharacterButton();
	void clickKephiCharacterButton();
	void clickEthiCharacterButton();
	void clickMosCharacterButton();
	void clickUniCharacterButton();
	void clickDizniCharacterButton();
	void clickSuCharacterButton();
	void clickHooUCharacterButton();
	void clickRayCharacterButton();
	void clickRandomCharacterButton();



	void loadAvailableCharacterButton();
	std::vector<class CommonTexture*> vecAvailableCharacterButton;
	CharacterList CurrentSelectCharacter = CharacterList::Max;
	



	void loadCharacterTraits();
	class CharacterTraits* m_CharacterTraits = nullptr;

	const float4 m_CharacterTraitsStartPos = float4{ 276.0f , 56.0f };


	void loadFadeScreen();
	class FadeScreen* m_FadeScreen = nullptr;
	const int m_FadeScreenAlphaValue = 70;


	void updateFirstElementUIVisibility();

	bool m_ButtonUpdateValue = true;



};

