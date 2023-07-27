#pragma once

enum class UpdateOrder
{
	Map,
	UI,
	Max,
};

enum class RenderOrder
{
	BackGround,
	GroundTile,
	StructureTile,
	SelectTile,
	FirstButtonUI,
	SecondButtonUI,
	MouseUI,
};

enum class CollisionOrder
{
};

enum class TileObjectOrder
{
	Structure = 1,
	NonMoveBlock,
	MoveBlock,
	Item,
	Monster,
	Character,
	Bubble,
	PopRange,
};