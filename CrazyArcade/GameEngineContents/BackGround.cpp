#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "BackGround.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

void BackGround::Start()
{
	Renderer = CreateRenderer(RenderOrder::BackGround);
	Renderer->On();
}

void BackGround::Update(float _Delta)
{

}

void BackGround::Init(const std::string& _FileName, float _RenderScaleRatio)
{
	GameEngineWindowTexture* Texture = GlobalUtils::TextureFileLoad(_FileName, "Resources\\Textures\\BackGround\\");
	
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Texture->GetScale() * _RenderScaleRatio);
}