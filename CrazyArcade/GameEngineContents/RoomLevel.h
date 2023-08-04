#pragma once
#include "ContentLevel.h"
#include "ActorEnum.h"

#include <vector>


enum class ButtonActor
{
	MapSelect,
	GameStart,
	GameExit,
	Max,
};

enum class WindowPanelActor
{
	MapSelect,

	Max,
};


enum class AvailableCharacterList
{
	Bazzi,
	Dao,
	Marid,
	Kephi,
	Random,
	Max,
};


struct CharacterSelectUI
{
public:
	class CommonTexture* OutlineTexture = nullptr;
	class CommonTexture* SelectButton = nullptr;
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

	const float4 m_GameExitButtonStartPos = float4{ 749.0f, 572.0f };




	void loadCharacterButton();
	std::vector<Button*> vecCharacterButton;
	float4 m_CharacterButtonScale = float4::ZERO;

	const float4 m_CharacterButtonStartPos = float4{ 489.0f , 83.0f };
	const float4 m_SpacingBTWCharacterButton = float4{ 7.0f, 4.0f };


	void clickSelectButton();
	void clickBazziCharacterButton();
	void clickDaoCharacterButton();
	void clickMaridCharacterButton();
	void clickKephiCharacterButton();
	void clickUnavailableCharacterButton();
	void clickRandomCharacterButton();


	AvailableCharacterList SelectAvailableCharacter = AvailableCharacterList::Max;
	CharacterList SelectCharacter = CharacterList::Max;

	void loadAvailableCharacterButton();
	int AvailableCharacterCount = static_cast<int>(AvailableCharacterList::Max);
	const float4 m_SelectedCharacterButtonStartPos = float4{ 487.0f , 81.0f };
	const float4 m_SpacingBTWSelectedCharacterButton = float4{ 3.0f , 0.0f };
	std::vector<CharacterSelectUI> vecCharacterSelectUI;
	const float4 m_CharacterOutlineStartPos = float4{ 490.f , 22.0f };

	void changeSelectedCharacterUI(CharacterList _Order);

	void loadSelectChecker();
	class CommonTexture* m_SelectChecker = nullptr;
	float4 m_SelectCheckerPosToButton = float4::ZERO;


	void loadCharacterTraits();
	class CharacterTraits* m_CharacterTraits = nullptr;

	const float4 m_CharacterTraitsStartPos = float4{ 276.0f , 56.0f };


	void loadFadeScreen();
	class FadeScreen* m_FadeScreen = nullptr;
	const int m_FadeScreenAlphaValue = 70;


	void updateFirstElementUIVisibility();

	bool m_ButtonUpdateValue = true;



};

