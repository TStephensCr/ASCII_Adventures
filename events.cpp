#include "hpp-files/events.hpp"

Events::Events(Entities* MyEntities){
    entitiesOBJ = MyEntities;

	InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();

	curwin      = entitiesOBJ->ReturnCurwin();

}

void Events::UpdateVariables(){
	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
	InfoPlayer    = entitiesOBJ->ReturnPlayerOBJ();
}

void Events::mvright(ens myEntity, int Force) {
    if (myEntity) {
        if (myEntity->xForce <= MaxForce)
            myEntity->xForce += Force;
    }
}

void Events::mvleft(ens myEntity, int Force) {
    if (myEntity) {
        if (myEntity->xForce >= MaxForce * -1)
            myEntity->xForce -= Force;
    }
}

void Events::mvdown(ens myEntity) {
    if (myEntity)
        myEntity->yForce += 1;
}

void Events::JumpStraight(int Height) {
    if (!InfoPlayer->inJump) {
        // Make the entity jump only if it's on the ground (i.e., yForce is zero)
        if (PlayerPointer->yForce == 0)
            PlayerPointer->yForce -= Height;
    }
}

void Events::Jump(int Height){	
	if (!InfoPlayer->inJump) {
        if (PlayerPointer->yForce == 0)
            PlayerPointer->yForce -= Height;

		if (InfoPlayer->LastMovement == 'd')
			mvright(PlayerPointer, Height);
		else 
			mvleft(PlayerPointer, Height);
    }
}
int Events::getmv() {
	int choice = wgetch(curwin);

	UpdateVariables();

	if (PlayerPointer && InfoPlayer) {
		switch (choice) {
		case KEY_RIGHT:
			InfoPlayer->LastMovement = 'd';
			mvright(PlayerPointer,1);
			break;
		case KEY_LEFT:
			InfoPlayer->LastMovement = 's';
			mvleft(PlayerPointer,1);
			break;
		case KEY_DOWN:
			mvdown(PlayerPointer);
			break;
		case ' ':
			JumpStraight(JUMPHEIGHT);
			break;
		case KEY_UP:
			Jump(JUMPHEIGHT);
			break;
		}
	}
	return choice;
}

void Events::Gravity(ens myEntity) {
	if(myEntity)myEntity->yForce++;
}


