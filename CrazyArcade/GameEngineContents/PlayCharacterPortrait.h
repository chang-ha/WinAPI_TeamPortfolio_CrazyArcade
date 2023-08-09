#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GlobalValue.h"

#include <string>

enum class PlayPortraitState
{
	Idle,
	Lose,
	Max,
};


// 설명 :
class PlayCharacterPortrait : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayCharacterPortrait();
	~PlayCharacterPortrait();

	// delete Function
	PlayCharacterPortrait(const PlayCharacterPortrait& _Other) = delete;
	PlayCharacterPortrait(PlayCharacterPortrait&& _Other) noexcept = delete;
	PlayCharacterPortrait& operator=(const PlayCharacterPortrait& _Other) = delete;
	PlayCharacterPortrait& operator=(PlayCharacterPortrait&& _Other) noexcept = delete;


	void initPortrait(CharacterList _Character)
	{
		initPortrait(static_cast<int>(_Character));
	}

	void initPortrait(int _Value);


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	// this
	GameEngineRenderer* Renderer = nullptr;

	void loadPortrait();

	PlayPortraitState m_State = PlayPortraitState::Max;

	void updateState(float _Delta);
	void changeState(PlayPortraitState _State);
	void changeAnimationAndSetRenderScale();

	float4 m_PortraitScale = float4::ZERO;
};

