#include "hpp-files/Logic.hpp"

Logic::Logic(WINDOW* win, WINDOW* menuuwin) {

	curwin      = win;

	entitiesOBJ = new Entities(win);

	InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();

	collision   = new Collision(entitiesOBJ);

	eventi      = new Events(entitiesOBJ);

	map         = new Mappa(win);

	Status      = Game;

	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();

	menuwin = menuuwin;

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
	curLev_ = curLev;
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

	myfile<<'C'<<bot_clock<<'\n';//pacing del gioco

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

		ReadGeneral();

		ReadPlayer();

		ReadEntities();
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

			DisplayPlayerStats();

			HandleBot(tmp);
			
			collision->ManageCollisions(tmp, curmap_, curLev_);

			if(!tmp->death_flag){//questo perche' in ManageCollisions l'entita' potrebbe morire				

            	entitiesOBJ->MoveEntity(tmp);

            	eventi->DecreaseForce(tmp);

           		entitiesOBJ->Display(tmp);
			}
        }

        tmp = tmp->next;
    }

    IncrementCounters();
}