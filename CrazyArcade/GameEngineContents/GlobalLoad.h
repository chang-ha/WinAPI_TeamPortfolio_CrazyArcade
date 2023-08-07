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

	static const int GroundMaxIndex = 11; 
	static const int StructureMaxIndex = 13;
	static const int ImmovableBlockMaxIndex = 4;
	static const int MovableBlockMaxIndex = 3;


	static void LoadMapInfoTexture();

protected:

private:
	static bool LoadTexture;
};