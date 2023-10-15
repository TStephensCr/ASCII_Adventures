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

void Events::Shoot(ens Entity, char Last_movement)
{
    int xPos = Entity->pos->ReturnPos().x;
    int yPos = Entity->pos->ReturnPos().y;
    int xDelta = (Last_movement == 'd') ? 1 : -1;

    MyPosition newP;
    newP.x = xPos + xDelta;
    newP.y = yPos;  

    ens Entity_in_new_loc = entitiesOBJ->EntitiesInLocation(newP, -1, -1);

    if (Entity_in_new_loc)
    {
		InfoPlayer->colpi--;
        entitiesOBJ->KillEntity(Entity_in_new_loc);
		if(Entity->type == player)
        	InfoPlayer->points += KILL_ENEMYS_POINTS;
    }
    else
    {
        char g = mvwinch(curwin, yPos, xPos + xDelta);
        if (g != HORIZONTAL_WALL && g != VERTICAL_WALL && g != FULLFILL_POINT && (InfoPlayer->colpi > 0 || Entity->type == enemy))
        {
            ens sparo = entitiesOBJ->Insert(shoot, xPos + xDelta, yPos);
            sparo->xForce = (Last_movement == 'd') ? 200 : -200;
			if(Entity->type == player)
            	InfoPlayer->colpi--;
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
			mvright(1);
			break;
		case KEY_LEFT:
			InfoPlayer->LastMovement = 's';
			mvleft(1);
			break;
		case KEY_DOWN:
			Shoot(PlayerPointer,InfoPlayer->LastMovement);
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