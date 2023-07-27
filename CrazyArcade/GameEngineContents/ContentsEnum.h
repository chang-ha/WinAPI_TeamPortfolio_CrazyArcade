#pragma once

enum class UpdateOrder
{
	Map,
	Character
};

enum class RenderOrder
{
	BackGround,
	Map,
	SelectTile,
	Character
};

enum class CollisionOrder
{
};

enum class TileObjectOrder
{
	Empty,
	Structure,
	ImmovableBlock,
	MovableBlock,
	Item,
	Monster,
	Character,
	Bubble,
	PopRange,
};