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
	Shadow,
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
	PlayerBody
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