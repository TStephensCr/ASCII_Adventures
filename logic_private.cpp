#include "hpp-files/Logic.hpp"

void Logic::UpdateVariables()
{
	InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();
	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();

	PlayerPointer->livello = curLev_;
	PlayerPointer->mappa = curmap_;

	map->leggimappa(curmap_);
    map->stampamappa();
}

void Logic::DisplayPlayerStats() {//al momento vengono stampati un menuwin, ma non va bene perchè si aggiorna solo quando accedi al menu con esc
    int x, y;
    getmaxyx(curwin, y, x);

    if (InfoPlayer) {
        mvwprintw(curwin, 2, x - 28, "                          ");
		mvwprintw(curwin, 3, x - 28, "                          ");
		mvwprintw(curwin, 4, x - 28, "                          "); 
		mvwprintw(curwin, 5, x - 28, "                          "); 
        mvwprintw(curwin, 2, x - 28, "hp : ");

        int health = InfoPlayer->hp;
        int bars = health / 5; // Calcola il numero di / basato sulla vita

        for (int i = 0; i < bars; i++) {
            waddch(curwin, '/');
        }
		mvwprintw(curwin, 3, x - 28, "soldi : %d",InfoPlayer->Money);
		mvwprintw(curwin, 4, x - 28, "colpi : %d",InfoPlayer->colpi);
		mvwprintw(curwin, 5, x - 28, "punti : %d",InfoPlayer->points);
    }
}

void Logic::CheckChangeMap() {
    int x, y;
    getmaxyx(curwin, y, x);

    int playerXloc = PlayerPointer->pos->ReturnPos().x;
    int playerYloc = PlayerPointer->pos->ReturnPos().y;

    if ((playerXloc == 1 && playerYloc == 12) || (playerXloc == x - 2 && playerYloc == 12)) {
        if (playerXloc == 1 && playerYloc == 12) {
            if (curmap_ == 1 && curLev_ > 0) {
                curmap_ = 5;
                curLev_--;
                PlayerPointer->pos->SelectPosition(x - 3, Y_PLAYERSPAWN);
            } else {
                if(curLev_ > 0){
					 curmap_--; 
					 PlayerPointer->pos->SelectPosition(x - 3, Y_PLAYERSPAWN);
				}else{
					 PlayerPointer->pos->SelectPosition(X_PLAYERSPAWN, Y_PLAYERSPAWN); 
				}
            }
        } else if (playerXloc == x - 2 && playerYloc == 12) {
            if (curmap_ == 5 && curLev_ < 2) {
                curLev_++;
                curmap_ = 1;
                PlayerPointer->pos->SelectPosition(X_PLAYERSPAWN, Y_PLAYERSPAWN);
            } else {
                curmap_++;
                PlayerPointer->pos->SelectPosition(X_PLAYERSPAWN, Y_PLAYERSPAWN);
            }
        }
    }
}

void Logic::HandleBot(ens entity) {
    if (entity->type == enemy && bot_clock == 3) {
		if(entity->livello == 2){
			if(counter_bot[curmap_ - 1][curLev_] == 4){
				eventi->Shoot(entity,'d');
			}
			else if(counter_bot[curmap_ - 1][curLev_] == 13){
				eventi->Shoot(entity,'s');
			}
		}
        if (counter_bot[curmap_ - 1][curLev_] < 9) {
            entity->xForce = 1;
        } else if (counter_bot[curmap_ - 1][curLev_] >= 9 && counter_bot[curmap_ - 1][curLev_] < 18) {
            entity->xForce = -1;
        }
    }
}

void Logic::IncrementCounters() {
    bot_clock++;

    if (bot_clock > 3) {
        counter_bot[curmap_ - 1][curLev_]++;
        bot_clock = 0;
    }

    if (counter_bot[curmap_ - 1][curLev_] == 18) {
        counter_bot[curmap_ - 1][curLev_] = 0;
    }
}

void Logic::ReadGeneral(){
	char mychar;
	std::ifstream myfile;
	myfile.open("Salvataggio.txt");

	do{//mappa
		mychar=myfile.get();
		}while(mychar!='M');
		mychar = myfile.get();
		curmap_ = mychar - '0';//per ottenere il valore int di un numero letto come char si sottrae il valore int assegnato a '0' al valore in assegnato al char letto('3'=51, '0'=48, 51-48=3)

		do{//livello
			mychar=myfile.get();
		}while(mychar!='L');
		mychar = myfile.get();
		curLev_ = mychar - '0';

		do{//bot_clock
			mychar=myfile.get();
		}while(mychar!='C');
		mychar = myfile.get();
		bot_clock = mychar - '0';


		char number_str[3];
		char *output;
		do{//counter_bot
			mychar=myfile.get();
		}while(mychar!='B');
		mychar = myfile.get();//il carattere \n
		for(int i=0;i<3;i++){
			for(int j=0;j<5;j++){
				number_str[0]=myfile.get();
				number_str[1]=myfile.get();
				counter_bot[j][i] = strtol(number_str, &output, 10);
				j++;
				if(number_str[1] != '.')
					mychar = myfile.get();
			}
			i++;
		}

	myfile.close();
}

void Logic::ReadPlayer(){//manca leggere posizione per l'insert
		char mychar;
		std::ifstream myfile;
		myfile.open("Salvataggio.txt");
		char number_str[3];
		char *output;

		Entities* tmpEns = ReturnEntitiesOBJ();
		ens tmp = tmpEns->Insert(player, 0, 0,curmap_,curLev_);

		do{//hp
			mychar=myfile.get();
		}while(mychar!='h');
		mychar=myfile.get();
		if(number_str[0] != '0'){
			number_str[1]=myfile.get();
			number_str[2]=myfile.get();
			InfoPlayer->hp = strtol(number_str, &output, 10);
		}
		else
			InfoPlayer->hp = 0;
		number_str[2] = NULL;

		do{//soldi
			mychar=myfile.get();
		}while(mychar!='s');
		number_str[0]=myfile.get();
		number_str[1]=myfile.get();
		InfoPlayer->Money = strtol(number_str, &output, 10);

		do{//colpi
			mychar=myfile.get();
		}while(mychar!='p');
		mychar = myfile.get();
		InfoPlayer->colpi = mychar - '0';

		do{//InJump
			mychar=myfile.get();
		}while(mychar!='b');
		mychar = myfile.get();
		if(mychar == '1')
			InfoPlayer->inJump = true;
		else InfoPlayer->inJump = false;

		myfile.close();
}

void Logic::ReadEntities(){
		char mychar;
		std::ifstream myfile;
		myfile.open("Salvataggio.txt");
		char number_str[3];
		char *output;

		Entities* tmpEns = ReturnEntitiesOBJ();
		EntityType type;//entita
		mychar = myfile.get();
		while(mychar != '<'){//valore di fine file
			do{//type
				mychar=myfile.get();
			}while(mychar!='t');
			mychar = myfile.get();
			switch(mychar){
				case 1:
					type = enemy;
				case 2:
					type = money;
				case 4:
					type = powerup;
			}

			int xtemp, ytemp;
			do{//position
				mychar=myfile.get();
			}while(mychar!='P');
			number_str[0]=myfile.get();
			number_str[1]=myfile.get();
			xtemp = strtol(number_str, &output, 10);
			if(number_str[1] != '.')
				mychar = myfile.get();
			number_str[0]=myfile.get();
			number_str[1]=myfile.get();
			ytemp = strtol(number_str, &output, 10);

			do{//mappa entita
				mychar=myfile.get();
			}while(mychar!='m');
			mychar = myfile.get();
			int mappatemp = mychar - '0';

			do{//livello entita
				mychar=myfile.get();
			}while(mychar!='l');
			mychar = myfile.get();
			int livellotemp = mychar - '0';

			ens tmp = tmpEns->Insert(type, xtemp, ytemp,mappatemp,livellotemp);
			

			do{//death flag
				mychar=myfile.get();
			}while(mychar!='D');
			if(mychar == '1')
			tmp->death_flag = true;
			else tmp->death_flag = false;

			do{//xForce
				mychar=myfile.get();
			}while(mychar!='x');
			mychar = myfile.get();
			tmp->xForce = mychar - '0';

			do{//yForce
				mychar=myfile.get();
			}while(mychar!='y');
			mychar = myfile.get();
			tmp->yForce = mychar - '0';

			mychar = myfile.get();
		}

		myfile.close();
}