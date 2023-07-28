#pragma once

enum class UpdateOrder
{
	Map,
	UI,
	Max,
	Character
};

enum class RenderOrder
{
	BackGround,
	Map,
	MapObject,
	SelectTile,
	FirstButtonUI,
	WindowPanelUI,
	SecondButtonUI,
	MouseUI,
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