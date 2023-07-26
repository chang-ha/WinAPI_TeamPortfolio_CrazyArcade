#pragma once

enum class UpdateOrder
{
	Map,
};

enum class RenderOrder
{
	BackGround,
	GroundTile,
	StructureTile,
	SelectTile,
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