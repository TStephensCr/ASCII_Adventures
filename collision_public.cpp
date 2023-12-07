#include "hpp-files/Collision.hpp"

//----Constructor----//

Collision::Collision(Entities *MyEntities)
{
    entitiesOBJ = MyEntities;
    ListOfEntities = entitiesOBJ->ReturnList();
    curwin = entitiesOBJ->ReturnCurwin();
    InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();
    PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
}

//----set functions----//

void Collision::setDifficulty(int newDifficulty)
{
    difficulty = newDifficulty;
}

//----Collision management functions----//

void Collision::ManageJump(entita_p Entity)
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

void Collision::OutOfBounds(entita_p Entity)
{
    int x, y;
    getmaxyx(curwin, y, x);

    if (Entity->type == player)
    {
        if (PlayerPointer->pos.y > y - 5)
        {
            entitiesOBJ->inflictDamageToPlayer(FALL_DAMAGE * difficulty);
            entitiesOBJ->ClearPosition(PlayerPointer);
            PlayerPointer->pos.Select(X_PLAYERSPAWN, Y_PLAYERSPAWN - 1);
        }
    }
    else if (Entity->type == shoot)
    {
        if (Entity->pos.x > x - 3 || Entity->pos.x < 2)
            entitiesOBJ->KillEntity(Entity);
    }
}

void Collision::ManageCollisions(entita_p Entity)
{
    if (!Entity)
        return;

    UpdateVariables();

    ManageJump(Entity);

    OutOfBounds(Entity);

    handleCollisions(Entity);
}
