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
	FirstElementUI,
	FadeScreenUI = 10,
	WindowPanelUI,
	SecondElementUI,
	MouseUI = 20,
	FadeOutUI,
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