#pragma once

enum class UpdateOrder
{
	Map,
};

enum class RenderOrder
{
	BackGround,
	Map,
	SelectTile,
};

enum class CollisionOrder
{
};

enum class TileObjectOrder
{
	Structure = 1,
	ImmovableBlock,
	MovableBlock,
	Item,
	Monster,
	Character,
	Bubble,
	PopRange,
};