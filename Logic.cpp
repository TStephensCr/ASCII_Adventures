#include "hpp-files/Logic.hpp"
#include <fstream>

Logic::Logic(WINDOW* win) {

	curwin      = win;

	entitiesOBJ = new Entities(win);

	InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();

	collision   = new Collision(entitiesOBJ);

	eventi      = new Events(entitiesOBJ);

	map         = new Mappa(win);

	Status      = Game;

	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
}

Events *Logic::ReturnEventsOBJ()
{
    return eventi;
}

Entities *Logic::ReturnEntitiesOBJ()
{
    return entitiesOBJ;
}

Player* Logic::ReturnInfoPlayer()
{
	return InfoPlayer;
}

void Logic::InitMappa(int curmap, int curLev){
	curmap_ = curmap;
	map->leggimappa(curmap);
    map->stampamappa();
}

void Logic::UpdateVariables()
{
	InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();
	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();

	PlayerPointer->livello = curLev_;
	PlayerPointer->mappa = curmap_;

	map->leggimappa(curmap_);
    map->stampamappa();
}


void Logic::FileSave(){
	char mychar;
	std::ofstream myfile;
	myfile.open("Salvataggio.txt");
	myfile.put('A');
	myfile.close();
}

void Logic::InitEntities(){//facciamo initentities ogni volta che il player aumenta di livello.
										 //e quando lo fai metti la lista entities = NULL
										 // il livello corrente è quello che metto quando faccio initEntities
										 //bisogna mettere una caratteristica alle entità chiamata livello
	entitiesOBJ->Insert(player, X_PLAYERSPAWN , Y_PLAYERSPAWN);

	for(int x = 0; x < 3; x++){
		// Continue assigning variables for maps 1, 2, 3, 4, and 5 with mappa and livello values
		ens entita_1_1 = entitiesOBJ->Insert(money, 26, 4); 
		entita_1_1->mappa = 1; 
		entita_1_1->livello = x;
		if (x >= 0) {
			ens entita_1_2 = entitiesOBJ->Insert(enemy, 21, 11); 
			entita_1_2->mappa = 1; 
			entita_1_2->livello = x;
		}
		if (x >= 1) {
			ens entita_1_3 = entitiesOBJ->Insert(enemy, 36, 6); 
			entita_1_3->mappa = 1; 
			entita_1_3->livello = x;
		}
		if (x >= 2) {
			ens entita_1_4 = entitiesOBJ->Insert(enemy, 55, 9); 
			entita_1_4->mappa = 1; 
			entita_1_4->livello = x;
		}
		ens entita_1_5 = entitiesOBJ->Insert(money, 78, 8); 
		entita_1_5->mappa = 1; 
		entita_1_5->livello = x;

		ens entita_2_1 = entitiesOBJ->Insert(money, 31, 12); 
		entita_2_1->mappa = 2; 
		entita_2_1->livello = x;
		if (x >= 0) {
			ens entita_2_2 = entitiesOBJ->Insert(enemy, 16, 9); 
			entita_2_2->mappa = 2; 
			entita_2_2->livello = x;
		}
		if (x >= 1) {
			ens entita_2_3 = entitiesOBJ->Insert(enemy, 38, 8); 
			entita_2_3->mappa = 2; 
			entita_2_3->livello = x;
		}
		ens entita_2_4 = entitiesOBJ->Insert(money, 54, 12); 
		entita_2_4->mappa = 2; 
		entita_2_4->livello = x;
		ens entita_2_5 = entitiesOBJ->Insert(powerup, 68, 14); 
		entita_2_5->mappa = 2; 
		entita_2_5->livello = x;
		if (x >= 2) {
			ens entita_2_6 = entitiesOBJ->Insert(enemy, 77, 10); 
			entita_2_6->mappa = 2; 
			entita_2_6->livello = x;
		}

		ens entita_3_1 = entitiesOBJ->Insert(money, 22, 5); 
		entita_3_1->mappa = 3; 
		entita_3_1->livello = x;
		ens entita_3_2 = entitiesOBJ->Insert(powerup, 22, 14); 
		entita_3_2->mappa = 3; 
		entita_3_2->livello = x;
		if (x >= 0) {
			ens entita_3_3 = entitiesOBJ->Insert(enemy, 30, 11); 
			entita_3_3->mappa = 3; 
			entita_3_3->livello = x;
		}
		if (x >= 1) {
			ens entita_3_4 = entitiesOBJ->Insert(enemy, 32, 6); 
			entita_3_4->mappa = 3; 
			entita_3_4->livello = x;
		}
		ens entita_3_5 = entitiesOBJ->Insert(money, 60, 6); 
		entita_3_5->mappa = 3; 
		entita_3_5->livello = x;
		ens entita_3_6 = entitiesOBJ->Insert(money, 73, 13); 
		entita_3_6->mappa = 3; 
		entita_3_6->livello = x;

		ens entita_4_1 = entitiesOBJ->Insert(money, 37, 7); 
		entita_4_1->mappa = 4; 
		entita_4_1->livello = x;
		if (x >= 0) {
			ens entita_4_2 = entitiesOBJ->Insert(enemy, 51, 7); 
			entita_4_2->mappa = 4; 
			entita_4_2->livello = x;
		}
		if (x >= 1) {
			ens entita_4_3 = entitiesOBJ->Insert(enemy, 29, 13); 
			entita_4_3->mappa = 4; 
			entita_4_3->livello = x;
		}
		ens entita_4_4 = entitiesOBJ->Insert(money, 53, 13); 
		entita_4_4->mappa = 4; 
		entita_4_4->livello = x;
		if (x >= 2) {
			ens entita_4_5 = entitiesOBJ->Insert(enemy, 68, 11); 
			entita_4_5->mappa = 4; 
			entita_4_5->livello = x;
		}
		ens entita_4_6 = entitiesOBJ->Insert(powerup, 22, 10); 
		entita_4_6->mappa = 4; 
		entita_4_6->livello = x;

		ens entita_5_1 = entitiesOBJ->Insert(money, 42, 5); 
		entita_5_1->mappa = 5; 
		entita_5_1->livello = x;
		if (x >= 2) {
			ens entita_5_2 = entitiesOBJ->Insert(enemy, 19, 13); 
			entita_5_2->mappa = 5; 
			entita_5_2->livello = x;
		}
		if (x >= 0) {
			ens entita_5_3 = entitiesOBJ->Insert(enemy, 25, 9); 
			entita_5_3->mappa = 5; 
			entita_5_3->livello = x;
		}
		if (x >= 1) {
			ens entita_5_4 = entitiesOBJ->Insert(enemy, 49, 9); 
			entita_5_4->mappa = 5; 
			entita_5_4->livello = x;
		}
		ens entita_5_5 = entitiesOBJ->Insert(money, 73, 10); 
		entita_5_5->mappa = 5; 
		entita_5_5->livello = x;
		ens entita_5_6 = entitiesOBJ->Insert(powerup, 45, 14); 
		entita_5_6->mappa = 5; 
		entita_5_6->livello = x;

	}
}

void Logic::DisplayPlayerStats() {
    int x, y;
    getmaxyx(curwin, y, x);

    if (InfoPlayer) {
        mvwprintw(curwin, 2, x - 28, "                          ");
		mvwprintw(curwin, 3, x - 28, "                          ");
		mvwprintw(curwin, 4, x - 28, "                          "); 
		mvwprintw(curwin, 5, x - 28, "                          "); 
		mvwprintw(curwin, 6, x - 28, "                          "); 
        mvwprintw(curwin, 2, x - 28, "hp : ");

        int health = InfoPlayer->hp;
        int bars = health / 5; // Calcola il numero di / basato sulla vita

        for (int i = 0; i < bars; i++) {
            waddch(curwin, '/');
        }
		mvwprintw(curwin, 3, x - 28, "soldi : %d",InfoPlayer->Money);
		mvwprintw(curwin, 4, x - 28, "colpi : %d",InfoPlayer->colpi);
		mvwprintw(curwin, 5, x - 28, "punti : %d",InfoPlayer->points);
		mvwprintw(curwin, 6, x - 28, "punti : %d",PlayerPointer->pos->ReturnPos().y);
    }
}

void Logic::CheckChangeMap(){
	int x, y;
    getmaxyx(curwin, y, x);

	if(PlayerPointer->pos->ReturnPos().x == 1 && PlayerPointer->pos->ReturnPos().y == 12){
		if(curmap_ == 1){
			if(curLev_ > 0){
				curmap_ = 5;
				curLev_--;
				PlayerPointer->pos->SelectPosition(x - 3,Y_PLAYERSPAWN);
			}
		}
		else{
			curmap_--;
			PlayerPointer->pos->SelectPosition(x - 3,Y_PLAYERSPAWN);
		}
		
	}

	if(PlayerPointer->pos->ReturnPos().x == x-2 && PlayerPointer->pos->ReturnPos().y == 12){
		if(curmap_ == 5){
			if(curLev_ < 2){
				curLev_++;
				curmap_ = 1;
				PlayerPointer->pos->SelectPosition(X_PLAYERSPAWN,Y_PLAYERSPAWN);
			}
		}
		else{
			curmap_++;
			PlayerPointer->pos->SelectPosition(X_PLAYERSPAWN,Y_PLAYERSPAWN);
		}
	}
}

void Logic::GiveDynamicity()
{
    ens tmp = entitiesOBJ->ReturnList();
	
	UpdateVariables();
	CheckChangeMap();

    while (tmp) {
        if ((!tmp->death_flag) && (tmp->mappa == curmap_ || tmp->type == shoot) && (tmp->livello == curLev_ || tmp->type == shoot)) {
            if (tmp->type == enemy && counter == 3) {
                if (counter_bot[curmap_ - 1][curLev_] < 9) {
                    // Move to the right
                    tmp->xForce = 1;
                } else if (counter_bot[curmap_ - 1][curLev_] >= 9 && counter_bot[curmap_ - 1][curLev_] < 18) {
                    // Move to the left
                    tmp->xForce = -1;
                }
            }

			DisplayPlayerStats();
			
            entitiesOBJ->ClearPosition(tmp);

            eventi->Gravity(tmp);

            collision->ManageCollisions(tmp, curmap_, curLev_);

            entitiesOBJ->MoveEntity(tmp);

            entitiesOBJ->DecreaseForce(tmp);

            entitiesOBJ->Display(tmp);
        }

        tmp = tmp->next;
    }

    // Increment the counters
	counter++;
	if(counter > 3){
		counter_bot[curmap_ - 1][curLev_]++;
		counter = 0;
	}
		
	if(counter_bot[curmap_ - 1][curLev_] == 18)
		counter_bot[curmap_ - 1][curLev_] = 0;
}