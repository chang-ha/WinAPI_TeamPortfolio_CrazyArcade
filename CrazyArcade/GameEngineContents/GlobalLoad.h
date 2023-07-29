#pragma once

class GlobalLoad
{
public:
	// Constructor Destructor
	GlobalLoad();
	~GlobalLoad();

	// Delete Function
	GlobalLoad(const GlobalLoad& _Other) = delete;
	GlobalLoad(GlobalLoad&& _Other) noexcept = delete;
	GlobalLoad& operator=(const GlobalLoad& _Other) = delete;
	GlobalLoad& operator=(GlobalLoad&& _Other) noexcept = delete;

	static void TileTextureLoad();

protected:

private:
	static bool LoadTexture;
};