#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GlobalValue.h"

#include <vector>


enum class SpaceButtonState
{
	SpaceButton,
	UnspaceButton,
	Max,
};



// 설명 :
class CharacterRoomButton : public GameEngineActor
{
public:
	// constrcuter destructer
	CharacterRoomButton();
	~CharacterRoomButton();

	// delete Function
	CharacterRoomButton(const CharacterRoomButton& _Other) = delete;
	CharacterRoomButton(CharacterRoomButton&& _Other) noexcept = delete;
	CharacterRoomButton& operator=(const CharacterRoomButton& _Other) = delete;
	CharacterRoomButton& operator=(CharacterRoomButton&& _Other) noexcept = delete;

	void initCharacterRoomButton();

	bool isSpaceButtonState()
	{
		if (SpaceButtonState::SpaceButton == m_SpaceButtonState)
		{
			return true;
		}

		return false;
	}


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	// this
	bool m_HostValue = false;

	void loadSpaceButton();
	SpaceButtonState m_SpaceButtonState = SpaceButtonState::Max;

	void clickSpaceButton();
	void clickUnspaceButton();

	std::vector<class Button*> vecSpaceButton;
	float4 m_SpaceButtonScale = float4::ZERO;





	void loadSpaceCharacterComposition();
	AvailableCharacterList m_CurrentSelectedCharaterTexture = AvailableCharacterList::Max;

	std::vector<class CommonTexture*> vecCharacterTexture;

	class CommonTexture* m_CharacterShadow = nullptr;
	const float4 m_ShadowStartPosToRoomButton = float4{ 17.0f , 80.0f };


	class CommonTexture* m_ReadyBillboard = nullptr;
	const float4 m_BillBoardStartPosToEachRoom = float4{ 3.0f , 123.0f };


	class CommonTexture* m_Flag = nullptr;
	const float4 m_FlagStartPosToEachRoom = float4{ 58.0f , 46.0f };

	bool m_ActiveSpaceButtonValue = true;

};

