#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <string>


// ���� :
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
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;


	// this
	struct PlayPortraitInfo
	{
	public:


	};

};

