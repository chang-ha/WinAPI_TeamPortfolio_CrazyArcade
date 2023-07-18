#include <GameEngineCore/GameEngineCore.h>

#include <GameEngineContents/CrazyArcadeCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::EngineStart<CrazyArcadeCore>("CrazyArcade", hInstance);
	return 0;
}