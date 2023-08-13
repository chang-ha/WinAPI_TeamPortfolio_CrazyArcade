#pragma once

enum class CharacterState
{
	Idle,
	Move,
	Ready,
	FlashLong,
	FlashShort,
	BubbleHit,
	Bubble,
	BubbleEnd,
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
	Anger,
	AngerIdle,
	AngerMove,
	EggIdle,
	EggMove,
	EggSummon,
	EggDeath,
	Die,
	// Boss State
	Hitten,
	Summon,
	Die_Ready,
	Die_Bubble,
};