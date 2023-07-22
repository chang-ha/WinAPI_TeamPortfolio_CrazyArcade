#include "BaseCharacter.h"

void BaseCharacter::WaitStart()
{
	ChangeAnimationState("Wait");
}

void BaseCharacter::WaitUpdate(float _Delta)
{

}