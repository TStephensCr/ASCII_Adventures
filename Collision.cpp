#include "hpp-files/Collision.hpp"


Collision::Collision(Entities* MyEntities) {
	entitiesOBJ     = MyEntities;
	ListOfEntities  = entitiesOBJ->ReturnList();
	curwin          = entitiesOBJ->ReturnCurwin();
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

void Collision::OutOfBounds(){
    int x, y;
    getmaxyx(curwin, y, x);

    if(entitiesOBJ->ReturnPlayerPointer()->pos->ReturnPos().y > y - 5){
        entitiesOBJ->ReturnPlayerOBJ()->hp -= 20;
        entitiesOBJ->ClearPosition(entitiesOBJ->ReturnPlayerPointer());
        entitiesOBJ->ReturnPlayerPointer()->pos->SelectPosition(X_PLAYERSPAWN,Y_PLAYERSPAWN);
    }

}

void Collision::ManageCollisions(ens Entity,int mappa,int livello)
{
    if(Entity){
        int xPos = Entity->pos->ReturnPos().x;
        int yPos = Entity->pos->ReturnPos().y;

        ManageJump(Entity);

        OutOfBounds();
        
        if (Entity->yForce != 0) {
            int c = (Entity->yForce < 0) ? yPos - 1 : yPos + 1;
            char charAboveOrBelow = mvwinch(curwin, c, xPos);
            MyPosition newP;
            newP.x = xPos; newP.y = c;
            ens Entity_in_new_loc = entitiesOBJ->EntitiesInLocation(newP, mappa, livello);

            if (charAboveOrBelow == HORIZONTAL_WALL || charAboveOrBelow == VERTICAL_WALL || charAboveOrBelow == FULLFILL_POINT) {
                Entity->yForce = 0;
            }
            else if(Entity_in_new_loc && !Entity_in_new_loc->death_flag){//vedo i casi in cui è un entità
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
                    entitiesOBJ->ReturnPlayerOBJ()->hp -= 20;
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
            ens Entity_in_new_loc = entitiesOBJ->EntitiesInLocation(newP, mappa, livello);

            if (charAtNewPos == HORIZONTAL_WALL || charAtNewPos == VERTICAL_WALL || charAtNewPos == FULLFILL_POINT) {
                if(Entity->type == shoot)
                    Entity->death_flag = true;
                else
                    Entity->xForce = 0;
            }
            else if(Entity_in_new_loc && !Entity_in_new_loc->death_flag){
                if(Entity->type == player && Entity_in_new_loc->type == money){
                    Entity_in_new_loc->death_flag = true;
                    entitiesOBJ->ReturnPlayerOBJ()->Money += 1;
                }
                else if ((Entity->type == shoot && Entity_in_new_loc->type == enemy) || (Entity->type == enemy && Entity_in_new_loc->type == shoot)) {
                    Entity_in_new_loc->death_flag = true;
                    Entity->death_flag = true;
                    entitiesOBJ->ClearPosition(Entity_in_new_loc);
                }
// caso sparo/nemico e nemico/sparo [semplicemente entrambi si eliminano]
                else if(Entity_in_new_loc->type == enemy && Entity->type == player){
                    if(entitiesOBJ->ReturnPlayerOBJ()->LastMovement == 'd'){
                        Entity->xForce = -10; Entity->yForce = -10;
                    }
                    else{
                        Entity->xForce = 10; Entity->yForce = -10;
                    }
                    entitiesOBJ->ReturnPlayerOBJ()->hp -= 20;
                }// caso player tocca il nemico
                else if(Entity_in_new_loc->type == player && Entity->type == enemy){
                    if(Entity->xForce >= 1)
                        Entity_in_new_loc->xForce = 1 * 10;
                    else
                        Entity_in_new_loc->xForce = -1 * 10;

                    Entity_in_new_loc->yForce = -10;

                    entitiesOBJ->ReturnPlayerOBJ()->hp -= 20;
                }//caso nemico tocca il player
                else if(Entity_in_new_loc->type == powerup && Entity->type == player){
                    Entity_in_new_loc->death_flag = true;
                    entitiesOBJ->ReturnPlayerOBJ()->hp = 100;
                }//caso nemico tocca il player
            }
            //qua ci devo mettere un controllo su quando il player arriva nelle caselle di cambio mappa. Chiama funzione per salvataggio file e richiama InitMappa con valori nuovi
        }
    }
}
