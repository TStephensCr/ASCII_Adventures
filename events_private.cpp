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

void Events::Shoot(ens Entity)
{
    int xPos = Entity->pos->ReturnPos().x;
    int yPos = Entity->pos->ReturnPos().y;
    int xDelta = (InfoPlayer->LastMovement == 'd') ? 1 : -1;

    MyPosition newP;
    newP.x = xPos + xDelta;
    newP.y = yPos;  

    ens Entity_in_new_loc = entitiesOBJ->EntitiesInLocation(newP, -1, -1);

    if (Entity_in_new_loc)
    {
        Entity_in_new_loc->death_flag = true;
        InfoPlayer->points += KILL_ENEMYS_POINTS;
    }
    else
    {
        char g = mvwinch(curwin, yPos, xPos + xDelta);
        if (g != HORIZONTAL_WALL && g != VERTICAL_WALL && g != FULLFILL_POINT && InfoPlayer->colpi > 0)
        {
            ens sparo = entitiesOBJ->Insert(shoot, xPos + xDelta, yPos);
            sparo->xForce = (InfoPlayer->LastMovement == 'd') ? 200 : -200;
            InfoPlayer->colpi--;
        }
    }
}
