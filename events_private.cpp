#include "hpp-files/events.hpp"

void Events::UpdateVariables(){
	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
	InfoPlayer    = entitiesOBJ->ReturnPlayerOBJ();
}

void Events::mvright(int Force) {
	if (PlayerPointer->xForce <= MaxForce)
		PlayerPointer->xForce += Force;
}

void Events::mvleft(int Force) {
	if (PlayerPointer->xForce >= MaxForce * -1)
		PlayerPointer->xForce -= Force;
}

void Events::JumpStraight()
{
    if (!InfoPlayer->inJump) {
        if (PlayerPointer->yForce == 0)
            PlayerPointer->yForce -= JUMPHEIGHT;
    }
}

void Events::Jump(){	
if (!InfoPlayer->inJump) {
	if (PlayerPointer->yForce == 0)
		PlayerPointer->yForce -= JUMPHEIGHT;

	if (InfoPlayer->LastMovement == 'd')
		mvright(JUMPHEIGHT);
	else 
		mvleft(JUMPHEIGHT);
}
}

