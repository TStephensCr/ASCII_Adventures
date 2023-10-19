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

    int xPos = Entity->pos->ReturnPos().x;
    int yPos = Entity->pos->ReturnPos().y;
    char charBelow = mvwinch(curwin, yPos + 1, xPos);

    if (charBelow == ' ') {
        InfoPlayer->inJump = true;
    } else if (InfoPlayer->inJump) {
        InfoPlayer->inJump = false;
        Entity->xForce = 0;
    }
}


void Collision::OutOfBounds(){
    int x, y;
    getmaxyx(curwin, y, x);

    if(PlayerPointer->pos->ReturnPos().y > y - 5){
        InfoPlayer->hp -= FALL_DAMAGE;
        entitiesOBJ->ClearPosition(PlayerPointer);
        PlayerPointer->pos->SelectPosition(X_PLAYERSPAWN,5);
    }

}

void Collision::ManageCollisions(ens Entity, int mappa, int livello)
{
    if (!Entity)
        return;

    UpdateVariables();

    int xPos = Entity->pos->ReturnPos().x;
    int yPos = Entity->pos->ReturnPos().y;

    ManageJump(Entity);
    OutOfBounds();

    HandleVerticalCollision(Entity, xPos, yPos);
    HandleHorizontalCollision(Entity, xPos, yPos);
}



