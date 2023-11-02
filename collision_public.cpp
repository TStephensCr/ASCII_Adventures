#include "hpp-files/Collision.hpp"

Collision::Collision(Entities* MyEntities) {
	entitiesOBJ     = MyEntities;
	ListOfEntities  = entitiesOBJ->ReturnList();
	curwin          = entitiesOBJ->ReturnCurwin();
    InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();
	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
}

void Collision::ManageJump(ens Entity) {
    if (Entity != PlayerPointer)
        return;

    int xPos = Entity->pos.x;
    int yPos = Entity->pos.y;
    char charBelow = mvwinch(curwin, yPos + 1, xPos);

    if (charBelow != HORIZONTAL_WALL && charBelow != FULLFILL_POINT) {
        InfoPlayer->inJump = true;
    } else if (InfoPlayer->inJump) {
        InfoPlayer->inJump = false;
        Entity->xForce = 0;
    }
}


void Collision::OutOfBounds(){
    int y;
    y = getmaxy(curwin);

    if(PlayerPointer->pos.y > y - 5){
        InfoPlayer->hp -= FALL_DAMAGE;
        entitiesOBJ->ClearPosition(PlayerPointer);
        PlayerPointer->pos.Select(X_PLAYERSPAWN,5);
    }

}

void Collision::ManageCollisions(ens Entity)
{
    if (!Entity)
        return;

    UpdateVariables();

    int xPos = Entity->pos.x;
    int yPos = Entity->pos.y;

    ManageJump(Entity);
    OutOfBounds();

    HandleVerticalCollision(Entity, xPos, yPos);
    HandleHorizontalCollision(Entity, xPos, yPos);
}



