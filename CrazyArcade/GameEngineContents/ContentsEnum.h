#pragma once

enum class UpdateOrder
{
	Map,
	Character
};

enum class RenderOrder
{
	BackGround,
	GroundTile,
	StructureTile,
	SelectTile,
	Character
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