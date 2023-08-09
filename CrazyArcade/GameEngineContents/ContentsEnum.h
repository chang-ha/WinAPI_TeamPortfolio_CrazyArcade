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

enum class ItemType
{
	Bubble, // 물풍선 개수 1 증가
	Fluid, // 물줄기 길이 1 증가
	Ultra, // 물줄기 길이 최대치 증가
	Roller, // 이동속도 1 증가
	Red_Devil, // 이동속도 최대치 증가
	Needle, // 바늘
};

