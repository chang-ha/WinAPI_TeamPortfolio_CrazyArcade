#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "BackGround.h"
#include "ContentsEnum.h"

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
	GameEngineWindowTexture* Texture = nullptr;
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\BackGround\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));

		if (nullptr == Texture)
		{
			MsgBoxAssert("텍스처를 로드하지 못했습니다.");
			return;
		}
	}
	
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Texture->GetScale() * _RenderScaleRatio);
}