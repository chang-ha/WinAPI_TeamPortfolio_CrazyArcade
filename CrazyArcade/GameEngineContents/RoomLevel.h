#pragma once
#include "ContentLevel.h"
#include "GlobalValue.h"

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

class Button;
class WindowPanelUI;
class CommonTexture;
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

	const std::vector<std::string>& getCharacterString()
	{
		return vecCharacterString;
	}


	class CommonTexture* getChekcer2Pointer()
	{
		return m_SelectChecker2;
	}


public:
	static int g_SelectRoomNumber;

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
	const std::vector<std::string> vecCharacterString =
	{
		"Bazzi",
		"Dao",
		"Marid",
		"Kephi",
		"Ethi",
		"Mos",
		"Uni",
		"Dizni",
		"Su",
		"HooU",
		"Ray",
		"Random",
	};

	// 게임 창
	void loadWindowElement();
	std::vector<WindowPanelUI*> vecWindowPanel;


	// 선택된 맵 텍스처
	void loadSelectedMapComposition();

	struct SelectedMapInfo
	{
	public:
		CommonTexture* Img = nullptr;
		CommonTexture* Outline = nullptr;
	};

	SelectedMapInfo m_SelectedMapInfo;

	const float4 m_SelectedMapImgStarPos = float4{ 488.0f , 348.0f };
	const float4 m_SelectedMapOutlineStarPos = float4{ 642.0f , 346.0f };

	MapType m_CurMapType = MapType::Max;


	// 버튼
	void loadButtonElement();
	std::vector<Button*> vecButton;

	const float4 m_GameExitButtonStartPos = float4{ 749.0f, 572.0f };

	void clickGameStartButton();



	// 캐릭터 선택 버튼
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


	


	// 선택 가능한 버튼 요소
	void loadAvailableCharacterButton();
	class CommonTexture* OutlineTexture = nullptr;

	int AvailableCharacterCount = static_cast<int>(AvailableCharacterList::Max);
	const float4 m_SelectedCharacterButtonStartPos = float4{ 487.0f , 81.0f };
	const float4 m_SpacingBTWSelectedCharacterButton = float4{ 3.0f , 0.0f };
	std::vector<class CommonTexture*> vecSelectButton;
	const float4 m_CharacterOutlineStartPos = float4{ 490.f , 22.0f };

	void changeSelectedCharacterUI(CharacterList _Order);
	void changeOutline(CharacterList _Order);



	// 채크 텍스처
	void loadSelectChecker();
	class CommonTexture* m_SelectChecker1 = nullptr;
	class CommonTexture* m_SelectChecker2 = nullptr;
	float4 m_SelectChecker1PosToButton = float4::ZERO;
	float4 m_SelectChecker2PosToButton = float4::ZERO;

	// 캐릭터 트레잇(독립)
	void loadCharacterTraits();
	class CharacterTraits* m_CharacterTraits = nullptr;

	const float4 m_CharacterTraitsStartPos = float4{ 276.0f , 56.0f };



	// 각 방 버튼
	void loadRoomCharacterButton();
	const int m_AvailableRoomCount = 2;
	std::vector<class CharacterRoomButton*> vecCharacterRoomButton;

	float4 m_SelectRoomScale = float4::ZERO;

	const float4 m_CharacterRoomButtonStartPos = float4{ 26.0f , 112.0f };
	const float4 m_DistanceBTWCharacterRoomButton = float4{ 6.0f , 0.0f };


	// 방 경계선
	void loadSelectRoomBorder();
	std::vector<class CommonTexture*> vecSelectRoomBorder;


	// Fade
	void loadFadeScreen();
	class FadeScreen* m_FadeScreen = nullptr;


	// 업데이트
	void updateRoomDetectionChange();
	void updateSelectedMapDetectionChange();
	void updateCharacterRoomBorder();

	int returnCharacterRoomNumber();
	bool checkCharacterRoomOverMouse(int _Value);
	void changeBorder(int _Value);

	

	void updateFirstElementUIVisibility();

	bool m_ButtonUpdateValue = true;
};