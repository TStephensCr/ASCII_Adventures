#include "hpp-files/Collision.hpp"


Collision::Collision(Entities* MyEntities) {
	entitiesOBJ = MyEntities;
	ListOfEntities = entitiesOBJ->ReturnList();
	curwin = entitiesOBJ->ReturnCurwin();
}

void Collision::ManageJump(ens Entity){
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
            else if(Entity_in_new_loc){//vedo i casi in cui è un entità
                if(Entity->type == player && Entity_in_new_loc->type == money){//caso player/soldo
                    Entity_in_new_loc->death_flag = true;
                    entitiesOBJ->ReturnPlayerOBJ()->Money += 1;
                }
                else if(Entity_in_new_loc->type == enemy && Entity->type == player){
                    if(entitiesOBJ->ReturnPlayerOBJ()->LastMovement == 'd'){
                        Entity->xForce = -10; Entity->yForce = -10;
                    }
                    else{
                        Entity->xForce = 10; Entity->yForce = -10;
                    }
                    entitiesOBJ->ReturnPlayerOBJ()->hp -= 1;
                }
                else if(Entity_in_new_loc->type == powerup && Entity->type == player){
                    Entity_in_new_loc->death_flag = true;
                    entitiesOBJ->ReturnPlayerOBJ()->hp = 100;
                }//caso nemico tocca il player
                yPos = c;
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
                if(Entity->type == shoot)
                    Entity->death_flag = true;
                else
                    Entity->xForce = 0;
            }
            else if(Entity_in_new_loc){
                if(Entity->type == player && Entity_in_new_loc->type == money){
                    Entity_in_new_loc->death_flag = true;
                    entitiesOBJ->ReturnPlayerOBJ()->Money += 1;
                }
                else if((Entity_in_new_loc->type == enemy && Entity->type == shoot) || (Entity_in_new_loc->type == shoot && Entity->type == enemy)){
                    Entity_in_new_loc->death_flag = true;
                    Entity->death_flag = true;
                    entitiesOBJ->ClearPosition(Entity_in_new_loc);
                }// caso sparo/nemico e nemico/sparo [semplicemente entrambi si eliminano]
                else if(Entity_in_new_loc->type == enemy && Entity->type == player){
                    if(entitiesOBJ->ReturnPlayerOBJ()->LastMovement == 'd'){
                        Entity->xForce = -10; Entity->yForce = -10;
                    }
                    else{
                        Entity->xForce = 10; Entity->yForce = -10;
                    }
                    entitiesOBJ->ReturnPlayerOBJ()->hp -= 1;
                }// caso player tocca il nemico
                else if(Entity_in_new_loc->type == player && Entity->type == enemy){
                    if(Entity->xForce >= 1)
                        Entity_in_new_loc->xForce = 1 * 10;
                    else
                        Entity_in_new_loc->xForce = -1 * 10;

                    Entity_in_new_loc->yForce = -10;

                    entitiesOBJ->ReturnPlayerOBJ()->hp -= 1;
                }//caso nemico tocca il player
                else if(Entity_in_new_loc->type == powerup && Entity->type == player){
                    Entity_in_new_loc->death_flag = true;
                    entitiesOBJ->ReturnPlayerOBJ()->hp++;
                }//caso nemico tocca il player
            }
        }
    }
}
