#pragma once

enum class CharacterState
{
	Idle,
	Move,
	Ready,
	FlashLong,
	FlashShort,
	Bubble,
	Live,
	Die,
	Jump,
	Max
};

enum class ActorDir
{
	Left,
	Right,
	Up,
	Down,
};

enum class MonsterState
{
	Idle,
	Move,
	Ready,
	Freeze,
	Melt,
	Anger,
	Die,
	// Boss State
	Hitten,
	Summon,
};