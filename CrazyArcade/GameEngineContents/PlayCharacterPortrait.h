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
	float4 getPortraitScale() const
	{
		return m_PortraitScale;
	}

	void changeState(PlayPortraitState _State);

	void ActorRelease();

protected:

private:
	// GameEngineObject 상속
	void Start() override;


	// this
	GameEngineRenderer* Renderer = nullptr;

	void loadPortrait();
	float4 m_PortraitScale = float4::ZERO;


	PlayPortraitState m_State = PlayPortraitState::Max;

};

