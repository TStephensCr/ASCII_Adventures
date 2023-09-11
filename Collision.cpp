#include "hpp-files/Collision.hpp"


Collision::Collision(Entities* MyEntities) {
	entitiesOBJ = MyEntities;
	ListOfEntities = entitiesOBJ->ReturnList();
	curwin = entitiesOBJ->ReturnCurwin();
}

void Collision::ManageJump(ens Entity)
{
    int xPos = Entity->pos->ReturnPos().x;
    int yPos = Entity->pos->ReturnPos().y;
    
    if(Entity == entitiesOBJ->ReturnPlayerPointer()){
        char charBelow = mvwinch(curwin, yPos + 1, xPos);
        if(charBelow == ' ')
            entitiesOBJ->ReturnPlayerOBJ()->inJump = true;
        else{
            if(entitiesOBJ->ReturnPlayerOBJ()->inJump == true){
                entitiesOBJ->ReturnPlayerOBJ()->inJump = false;
                Entity->xForce = 0;
            }   
            else    
                entitiesOBJ->ReturnPlayerOBJ()->inJump = false;
        }
        
    }
}

void Collision::ManageCollisions(ens Entity) {
    if(Entity){
        int xPos = Entity->pos->ReturnPos().x;
        int yPos = Entity->pos->ReturnPos().y;

        ManageJump(Entity);
        
        if (Entity->yForce != 0) {
            int c = (Entity->yForce < 0) ? yPos - 1 : yPos + 1;
            char charAboveOrBelow = mvwinch(curwin, c, xPos);
            MyPosition newP;
            newP.x = xPos; newP.y = c;
            ens Entity_in_new_loc = entitiesOBJ->EntitiesInLocation(newP);

            if (charAboveOrBelow == HORIZONTAL_WALL || charAboveOrBelow == VERTICAL_WALL || charAboveOrBelow == FULLFILL_POINT) {
                Entity->yForce = 0;
            }
            else if(Entity_in_new_loc){
                if(Entity_in_new_loc->type == money){
                    Entity_in_new_loc->death_flag = true;
                    entitiesOBJ->ReturnPlayerOBJ()->Money += 1;
                    yPos = c;
                }
            }
            else{
                yPos = c;
            }
        }
        
        if (Entity->xForce != 0) {
            xPos = (Entity->xForce < 0) ? xPos - 1 : xPos + 1;
            char charAtNewPos = mvwinch(curwin, yPos, xPos);
             MyPosition newP;
            newP.x = xPos; newP.y = yPos;
            ens Entity_in_new_loc = entitiesOBJ->EntitiesInLocation(newP);

            if (charAtNewPos == HORIZONTAL_WALL || charAtNewPos == VERTICAL_WALL || charAtNewPos == FULLFILL_POINT) {
                Entity->xForce = 0;
            }
            else if(Entity_in_new_loc){
                if(Entity_in_new_loc->type == money){
                    Entity_in_new_loc->death_flag = true;
                    entitiesOBJ->ReturnPlayerOBJ()->Money += 1;
                }
            }
        }
    }
}
