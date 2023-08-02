#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class FadeScreen : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeScreen();
	~FadeScreen();

	// delete Function
	FadeScreen(const FadeScreen& _Other) = delete;
	FadeScreen(FadeScreen&& _Other) noexcept = delete;
	FadeScreen& operator=(const FadeScreen& _Other) = delete;
	FadeScreen& operator=(FadeScreen&& _Other) noexcept = delete;


	void setRenderScale(const float4& _Scale);

	void setAlpha(int _AlphaValue = 0);


protected:

private:
	// GameEngineObject 상속
	void Start() override;


	// this
	GameEngineRenderer* Renderer = nullptr;
	float4 m_Scale = float4::ZERO;

	int m_AlphaValue = 0;
};

