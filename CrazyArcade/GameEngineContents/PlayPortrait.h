#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <string>


// 설명 :
class PlayPortrait : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayPortrait();
	~PlayPortrait();

	// delete Function
	PlayPortrait(const PlayPortrait& _Other) = delete;
	PlayPortrait(PlayPortrait&& _Other) noexcept = delete;
	PlayPortrait& operator=(const PlayPortrait& _Other) = delete;
	PlayPortrait& operator=(PlayPortrait&& _Other) noexcept = delete;


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	// this
	struct PlayPortraitInfo
	{
	public:


	};

};

