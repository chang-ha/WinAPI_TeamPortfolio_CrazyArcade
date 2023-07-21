#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
class BackGround : public GameEngineActor
{
public:
	// constructer destructer
	BackGround();
	~BackGround();

	// delete function
	BackGround(const BackGround& _Ohter) = delete;
	BackGround(BackGround&& _Ohter) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void Init(const std::string& _FileName, float _RenderScaleRatio = 1.0f);

protected:

private:
	GameEngineRenderer* Renderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

