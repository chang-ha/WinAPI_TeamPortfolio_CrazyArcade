#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GlobalValue.h"

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


	void CreatePlayPortrait(int _PortraitNumber);

	class PlayCharacterPortrait* getPortrait()
	{
		if (m_PortraitInfo.Portrait)
		{
			return m_PortraitInfo.Portrait;
		}

		return nullptr;
	}

	void ActorRelease();

protected:

private:
	// GameEngineObject 상속
	void Start() override;


	// this
	struct PlayPortraitInfo
	{
	public:
		class PlayCharacterPortrait* Portrait = nullptr;
		class CommonTexture* Name = nullptr;
		class CommonTexture* Rank = nullptr;
	};

	PlayPortraitInfo m_PortraitInfo;

	const float4 CONST_PortraitStartPos = float4{ 7.0f , 5.0f };
	const float4 CONST_NameStartPos = float4{ 51.0f , 25.0f };
	const float4 CONST_RankStartPos = float4{ 54.0f , 6.0f };
};

