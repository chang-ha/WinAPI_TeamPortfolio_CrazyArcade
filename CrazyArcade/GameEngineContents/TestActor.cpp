#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "TestActor.h"

TestActor::TestActor()
{

}

TestActor::~TestActor()
{

}

void TestActor::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer();

	if (false == ResourcesManager::GetInst().IsLoadTexture("Title.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title.bmp"));
	}
	Renderer->SetTexture("Title.bmp");
	Renderer->SetRenderScale(GameEngineWindow::MainWindow.GetScale());
	Renderer->SetRenderPos(GameEngineWindow::MainWindow.GetScale().Half());
}

void TestActor::Update(float _Delta)
{

}