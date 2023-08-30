#include "hpp-files/Collision.hpp"


Collision::Collision(Entities* MyEntities) {
	entitiesOBJ = MyEntities;
	ListOfEntities = entitiesOBJ->ReturnList();
	curwin = entitiesOBJ->ReturnCurwin();
}


void Collision::ManageCollisions(ens Entity) {
    if(Entity){
        int xPos = Entity->pos->ReturnPos().x;
        int yPos = Entity->pos->ReturnPos().y;

        if(Entity == entitiesOBJ->ReturnPlayerPointer()){
            char charBelow = mvwinch(curwin, yPos + 1, xPos);
            if(charBelow == ' ')
                entitiesOBJ->ReturnPlayerOBJ()->inJump = true;
            else
                entitiesOBJ->ReturnPlayerOBJ()->inJump = false;
        }
        
        if (Entity->yForce != 0) {
            int c = (Entity->yForce < 0) ? yPos - 1 : yPos + 1;
            char charAboveOrBelow = mvwinch(curwin, c, xPos);
            
            if (charAboveOrBelow != ' ') {
                Entity->yForce = 0;
            }else{
                yPos = c;
            }
        }
        
        if (Entity->xForce != 0) {
            xPos = (Entity->xForce < 0) ? xPos - 1 : xPos + 1;
            char charAtNewPos = mvwinch(curwin, yPos, xPos);
            
            if (charAtNewPos != ' ') {
                Entity->xForce = 0;
            }
        }
    }

}