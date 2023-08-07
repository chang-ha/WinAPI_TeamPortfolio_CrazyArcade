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

	static const int GroundMaxIndex = 9; 
	static const int StructureMaxIndex = 5;
	static const int ImmovableBlockMaxIndex = 3;
	static const int MovableBlockMaxIndex = 2;


	static void LoadMapInfoTexture();

protected:

private:
	static bool LoadTexture;
};