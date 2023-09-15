#include "hpp-files/Logic.hpp"

Logic::Logic(WINDOW* win) {

	curwin      = win;

	entitiesOBJ = new Entities(win);

	InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();

	collision   = new Collision(entitiesOBJ);

	eventi      = new Events(entitiesOBJ);

	map         = new Mappa(win);

	Status      = Game;
}

Events *Logic::ReturnEventsOBJ()
{
    return eventi;
}

Entities *Logic::ReturnEntitiesOBJ()
{
    return entitiesOBJ;
}

void Logic::InitMappa(char curmap, int curLev){
	map->leggimappa(curmap);
    map->stampamappa();
	InitEntities(curmap, curLev);
}

void Logic::FileSave(){//cose da salvare: curmap, curLev, position e death_flag di tutte le entita di quella mappa(incluso il player)

}

void Logic::InitEntities(char NumberOfMap = '1', int curLev = 0){
	entitiesOBJ->Insert(player, X_PLAYERSPAWN , Y_PLAYERSPAWN);
	InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();

	if(NumberOfMap == '1'){
		entitiesOBJ->Insert(money, 26, 4);
		if(curLev >= 0)entitiesOBJ->Insert(enemy, 21, 11);
		if(curLev >= 1)entitiesOBJ->Insert(enemy, 36, 6);
		if(curLev >= 2)entitiesOBJ->Insert(enemy, 55, 9);
		entitiesOBJ->Insert(money, 78, 8);
	}
	else if(NumberOfMap == '2'){
		if(curLev >= 0)entitiesOBJ->Insert(enemy, 16, 9);
		entitiesOBJ->Insert(money, 31, 12);
		if(curLev >= 1)entitiesOBJ->Insert(enemy, 38, 8);
		entitiesOBJ->Insert(money, 54, 12);
		entitiesOBJ->Insert(powerup, 68, 14);
		if(curLev >= 2)entitiesOBJ->Insert(enemy, 77, 10);
	}
	else if(NumberOfMap == '3'){
		entitiesOBJ->Insert(money, 22, 5);
		entitiesOBJ->Insert(powerup, 22, 14);
		if(curLev >= 0)entitiesOBJ->Insert(enemy, 30, 11);
		if(curLev >= 1)entitiesOBJ->Insert(enemy, 32, 6);
		entitiesOBJ->Insert(money, 60, 6);
		entitiesOBJ->Insert(money, 73, 13);
		if(curLev >= 2)entitiesOBJ->Insert(enemy, 79, 10);
	}
	else if(NumberOfMap == '4'){
		entitiesOBJ->Insert(money, 37, 7);
		if(curLev >= 0)entitiesOBJ->Insert(enemy, 51, 7);
		if(curLev >= 1)entitiesOBJ->Insert(enemy, 29, 13);
		entitiesOBJ->Insert(money, 53, 13);
		if(curLev >= 2)entitiesOBJ->Insert(enemy, 68, 11);
		entitiesOBJ->Insert(powerup, 22, 10);
	}
	else if(NumberOfMap == '5'){
		entitiesOBJ->Insert(money, 42, 5);
		if(curLev >= 2)entitiesOBJ->Insert(enemy, 19, 13);
		if(curLev >= 0)entitiesOBJ->Insert(enemy, 25, 9);
		if(curLev >= 1)entitiesOBJ->Insert(enemy, 49, 9);
		entitiesOBJ->Insert(money, 73, 10);
		entitiesOBJ->Insert(powerup, 45, 14);
	}
}

void Logic::DisplayPlayerStats() {
    int x, y;
    getmaxyx(curwin, y, x);
    InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();

    if (InfoPlayer) {
        mvwprintw(curwin, 2, x - 28, "                          ");
		mvwprintw(curwin, 3, x - 28, "                          ");
		mvwprintw(curwin, 4, x - 28, "                          "); 
        mvwprintw(curwin, 2, x - 28, "hp : ");

        int health = InfoPlayer->hp;
        int bars = health / 5; // Calcola il numero di / basato sulla vita

        for (int i = 0; i < bars; i++) {
            waddch(curwin, '/');
        }
		mvwprintw(curwin, 3, x - 28, "soldi : %d",InfoPlayer->Money);
		mvwprintw(curwin, 4, x - 28, "colpi : %d",InfoPlayer->colpi);

    }
}


void Logic::GiveDynamicity()
{
    ens tmp = entitiesOBJ->ReturnList();
	
    while (tmp) {
        if (!tmp->death_flag) {
            if (tmp->type == enemy && counter == 3) {
                if (counter_bot < 9) {
                    // Move to the right
                    tmp->xForce = 1;
                } else if (counter_bot >= 9 && counter_bot < 18) {
                    // Move to the left
                    tmp->xForce = -1;
                }
            }

			DisplayPlayerStats();
			
            entitiesOBJ->ClearPosition(tmp);

            eventi->Gravity(tmp);

            collision->ManageCollisions(tmp);

            entitiesOBJ->MoveEntity(tmp);

            entitiesOBJ->DecreaseForce(tmp);

            entitiesOBJ->Display(tmp);
        }

        tmp = tmp->next;
    }

    // Increment the counters
	counter++;
	if(counter > 3){
		counter_bot++;
		counter = 0;
	}
		
	if(counter_bot == 18)
		counter_bot = 0;
}