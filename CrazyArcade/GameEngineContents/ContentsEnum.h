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
	Bubble, // ��ǳ�� ���� 1 ����
	Fluid, // ���ٱ� ���� 1 ����
	Ultra, // ���ٱ� ���� �ִ�ġ ����
	Roller, // �̵��ӵ� 1 ����
	Red_Devil, // �̵��ӵ� �ִ�ġ ����
	Needle, // �ٴ�
};

