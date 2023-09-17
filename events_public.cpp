#include "hpp-files/events.hpp"

Events::Events(Entities* MyEntities){
    entitiesOBJ = MyEntities;

	InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();

	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();

	curwin      = entitiesOBJ->ReturnCurwin();

}

void Events::PlayerGravity() {
	PlayerPointer->yForce++;
}

void Events::DecreaseForce(ens myEntity) {
	if(myEntity){
		if (myEntity->xForce <= -1)myEntity->xForce++;
		if (myEntity->xForce >= 1)myEntity->xForce--;
		if (myEntity->yForce <= -1)myEntity->yForce++;
		if (myEntity->yForce >= 1)myEntity->yForce--;
	}
}

int Events::getmv() {
	int choice = wgetch(curwin);

	UpdateVariables();

	if (PlayerPointer && InfoPlayer) {
		switch (choice) {
		case KEY_RIGHT:
			InfoPlayer->LastMovement = 'd';
			mvright(1);
			break;
		case KEY_LEFT:
			InfoPlayer->LastMovement = 's';
			mvleft(1);
			break;
		case KEY_DOWN:
			Shoot();
			break;
		case ' ':
			JumpStraight();
			break;
		case KEY_UP:
			Jump();
			break;
		}
	}
	return choice;
}