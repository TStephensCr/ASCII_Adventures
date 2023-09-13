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

void Events::JumpStraight()
{
    if (!InfoPlayer->inJump) {
        // Make the entity jump only if it's on the ground (i.e., yForce is zero)
        if (PlayerPointer->yForce == 0)
            PlayerPointer->yForce -= JUMPHEIGHT;
    }
}

void Events::Jump(){	
if (!InfoPlayer->inJump) {
	if (PlayerPointer->yForce == 0)
		PlayerPointer->yForce -= JUMPHEIGHT;

	if (InfoPlayer->LastMovement == 'd')
		mvright(PlayerPointer, JUMPHEIGHT);
	else 
		mvleft(PlayerPointer, JUMPHEIGHT);
}
}

void Events::Shoot()
{
	int xPos = PlayerPointer->pos->ReturnPos().x;
	int yPos = PlayerPointer->pos->ReturnPos().y;

	if(InfoPlayer->LastMovement == 'd'){
		char g = mvwinch(curwin, yPos, xPos + 1);
		if(g != HORIZONTAL_WALL && g != VERTICAL_WALL && g != FULLFILL_POINT){
			ens sparo = entitiesOBJ->Insert(shoot, xPos + 1, yPos);
			sparo->xForce = 200;
		}
	}else if(InfoPlayer->LastMovement == 's' ){
		char g = mvwinch(curwin, yPos, xPos - 1);
		if(g != HORIZONTAL_WALL && g != VERTICAL_WALL && g != FULLFILL_POINT){
			ens sparo = entitiesOBJ->Insert(shoot, xPos - 1, yPos);
			sparo->xForce = -200;
		}
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
			Shoot();
			//mvdown(PlayerPointer);
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

void Events::Gravity(ens myEntity) {
	if(myEntity && myEntity->type == player)myEntity->yForce++;
}