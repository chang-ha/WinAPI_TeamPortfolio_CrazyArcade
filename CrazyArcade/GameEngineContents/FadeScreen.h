#pragma once

// Ό³Έν :
class FadeScreen
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

protected:

private:

};

