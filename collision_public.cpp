#include "hpp-files/Collision.hpp"

Collision::Collision(Entities *MyEntities)
{
    entitiesOBJ = MyEntities;
    ListOfEntities = entitiesOBJ->ReturnList();
    curwin = entitiesOBJ->ReturnCurwin();
    InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();
    PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
}

void Collision::ManageJump(ens Entity)
{
    if (Entity != PlayerPointer)
        return;

    int xPos = InfoPlayer->previusPosition.x;
    int yPos = InfoPlayer->previusPosition.y;
    char charBelow = mvwinch(curwin, yPos + 1, xPos);

    if (charBelow != HORIZONTAL_WALL && charBelow != FULLFILL_POINT)
    {
        InfoPlayer->inJump = true;
    }
    else if (InfoPlayer->inJump)
    {
        InfoPlayer->inJump = false;
        Entity->xForce = 0;
    }
}

void Collision::OutOfBounds(ens Entity)
{
    int x, y;
    getmaxyx(curwin, y, x);

    if (Entity->type == player)
    {
        if (PlayerPointer->pos.y > y - 5)
        {
            InfoPlayer->hp -= FALL_DAMAGE;
            entitiesOBJ->ClearPosition(PlayerPointer);
            PlayerPointer->pos.Select(X_PLAYERSPAWN, Y_PLAYERSPAWN - 1);
            entitiesOBJ->KillEntity(PlayerPointer);
        }
    }
    else if (Entity->type == shoot)
    {
        if (Entity->pos.x > x - 3 || Entity->pos.x < 2)
            entitiesOBJ->KillEntity(Entity);
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
    OutOfBounds(Entity);

    HandleVerticalCollision(Entity, xPos, yPos);
    HandleHorizontalCollision(Entity, xPos, yPos);
}
