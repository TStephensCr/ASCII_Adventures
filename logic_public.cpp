#include "hpp-files/Logic.hpp"

Logic::Logic(WINDOW* win) {

	curwin      = win;

	entitiesOBJ = new Entities(win);

	InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();

	collision   = new Collision(entitiesOBJ);

	eventi      = new Events(entitiesOBJ);

	map         = new Mappa(win);

	Status      = Game;

	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();

	InitEntities();
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

void Logic::FileWrite(){//scrive il salvataggio su file
	char mychar;
	std::ofstream myfile;
	myfile.open("Salvataggio.txt", std::ofstream::trunc);

	myfile<<'E'<<'1'<<'\n';//file contiene salvataggio

	myfile<<'M'<<curmap_<<'\n';//mappa

	myfile<<'L'<<curLev_<<'\n';//livello

	myfile<<'C'<<counter<<'\n';//pacing del gioco

	myfile<<'B'<<'\n';//pacing dei bot
	for(int i=0;i<3;i++){
		for(int j=0;j<5;j++){
			myfile<<counter_bot[j][i]<<'.';
		}
		myfile<<'\n';
	}

	Player* tmpPlay = ReturnInfoPlayer();
	myfile<<'U'<<'\n';
	myfile<<'h'<<tmpPlay->hp<<'\n';
	myfile<<'s'<<tmpPlay->Money<<'\n';
	myfile<<'c'<<tmpPlay->colpi<<'\n';
	myfile<<'p'<<tmpPlay->points<<'\n';
	myfile<<'b'<<tmpPlay->inJump<<'\n';

	Entities* tmpEns = ReturnEntitiesOBJ();
	ens tmp = tmpEns->ReturnList();
	while(tmp->next != NULL){
		if(tmp->type!=3){
			myfile<<'_'<<'\n';
		
			myfile<<'t'<<tmp->type<<'\n';

			myfile<<'P'<<tmp->pos->ReturnPos().x<<'.'<<tmp->pos->ReturnPos().x<<'.'<<'\n';

			myfile<<'D'<<tmp->death_flag<<'\n';

			myfile<<'x'<<tmp->xForce<<'\n';

			myfile<<'y'<<tmp->yForce<<'\n';

			myfile<<'m'<<tmp->mappa<<'\n';

			myfile<<'l'<<tmp->livello<<'\n';
		}

		tmp=tmp->next;
	}

	myfile<<'<';

	myfile.close();
}//considerazioni per il read: dopo ogni valore di counter bot c'è un punto, il death flag è 0 vivo e 1 morto, tra i due valori di position c'è un punto, mi servira aiuto a interpretare il LastMovement del player
//ricorda di controllaore perchè il menu non funziona

void Logic::FileRead(){
	char mychar;
	std::ifstream myfile;
	myfile.open("Salvataggio.txt");
	mychar=myfile.get();//La E
	mychar=myfile.get();//il bool che dice se il file contiene salvataggi o no
	if(mychar == '1' && myfile.good()){

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

		do{//counter
			mychar=myfile.get();
		}while(mychar!='C');
		mychar = myfile.get();
		counter = mychar - '0';


		char number_str[3];
		char *output;
		do{//counter_bot
			mychar=myfile.get();
		}while(mychar!='B');
		mychar = myfile.get();//il carattere \n
		for(int i=0;i<3;i++){
			for(int j=0;j<5;j++){//qui ci sarebbe un
				number_str[0]=myfile.get();
				number_str[1]=myfile.get();
				counter_bot[j][i] = strtol(number_str, &output, 10);
				j++;
				if(number_str[1] != '.')
					mychar = myfile.get();
			}
			i++;
		}

		Player* tmpPlay = ReturnInfoPlayer();//player
		do{//hp
			mychar=myfile.get();
		}while(mychar!='h');
		mychar=myfile.get();
		if(number_str[0] != '0'){
			number_str[1]=myfile.get();
			number_str[2]=myfile.get();
			tmpPlay->hp = strtol(number_str, &output, 10);
		}
		else
			tmpPlay->hp = 0;
		number_str[2] = NULL;

		do{//soldi
			mychar=myfile.get();
		}while(mychar!='s');
		number_str[0]=myfile.get();
		number_str[1]=myfile.get();
		tmpPlay->Money = strtol(number_str, &output, 10);

		do{//colpi
			mychar=myfile.get();
		}while(mychar!='p');
		mychar = myfile.get();
		tmpPlay->colpi = mychar - '0';

		do{//InJump
			mychar=myfile.get();
		}while(mychar!='b');
		mychar = myfile.get();
		if(mychar == '1')
			tmpPlay->inJump = true;
		else tmpPlay->inJump = false;

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

			ens tmp = tmpEns->Insert(type, xtemp, ytemp);
			

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

			do{//mappa entita
				mychar=myfile.get();
			}while(mychar!='m');
			mychar = myfile.get();
			tmp->mappa = mychar - '0';

			do{//livello entita
				mychar=myfile.get();
			}while(mychar!='l');
			mychar = myfile.get();
			tmp->livello = mychar - '0';

			mychar = myfile.get();
		}
		//ritornare i valori letti/chiamare le funzioni di init da salvataggio
	}
	
}

void Logic::GiveDynamicity()
{
    ens tmp = entitiesOBJ->ReturnList();
	
	UpdateVariables();

	CheckChangeMap();
	
	eventi->PlayerGravity();
	
    while (tmp) {
        if ((!tmp->death_flag) && (tmp->mappa == curmap_ || tmp->type == shoot) && (tmp->livello == curLev_ || tmp->type == shoot)) {
            HandleBot(tmp);

			DisplayPlayerStats();
			
            entitiesOBJ->ClearPosition(tmp);

            collision->ManageCollisions(tmp, curmap_, curLev_);

            entitiesOBJ->MoveEntity(tmp);

            eventi->DecreaseForce(tmp);

            entitiesOBJ->Display(tmp);
        }

        tmp = tmp->next;
    }

    IncrementCounters();
}