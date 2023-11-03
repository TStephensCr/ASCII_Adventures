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

	maxX = getmaxx(curwin);
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

void Logic::ResetEntities(){
	entitiesOBJ->DeleteEntities();
	bot_clock = 0;
	PlayerTrackingQueue.clear();
	for(int i=0;i<3;i++){
		for(int j=0;j<5;j++){
			counter_bot[j][i]=0;
		}
	}
}

void Logic::InitEntities(){
	entitiesOBJ->Insert(player, X_PLAYERSPAWN , Y_PLAYERSPAWN, 1, 0);

	for (int x = 0; x < 3; x++) {
		entitiesOBJ->Insert(follower, 26, 4, 1, x);

		if (x >= 0) {
			entitiesOBJ->Insert(enemy, 21, 11, 1, x);
		}

		if (x >= 1) {
			entitiesOBJ->Insert(enemy, 36, 6, 1, x);
		}

		if (x >= 2) {
			entitiesOBJ->Insert(enemy, 55, 9, 1, x);
		}

		entitiesOBJ->Insert(money, 78, 8, 1, x);

		entitiesOBJ->Insert(money, 31, 12, 2, x);

		if (x >= 0) {
			entitiesOBJ->Insert(enemy, 16, 9, 2, x);
		}

		if (x >= 1) {
			entitiesOBJ->Insert(enemy, 38, 8, 2, x);
		}

		entitiesOBJ->Insert(money, 54, 12, 2, x);

		entitiesOBJ->Insert(powerup, 68, 14, 2, x);

		if (x >= 2) {
			entitiesOBJ->Insert(enemy, 77, 10, 2, x);
		}

		entitiesOBJ->Insert(money, 22, 5, 3, x);

		entitiesOBJ->Insert(powerup, 22, 14, 3, x);

		if (x >= 0) {
			entitiesOBJ->Insert(enemy, 30, 11, 3, x);
		}

		if (x >= 1) {
			entitiesOBJ->Insert(enemy, 32, 6, 3, x);
		}

		entitiesOBJ->Insert(money, 60, 6, 3, x);

		entitiesOBJ->Insert(money, 73, 13, 3, x);

		entitiesOBJ->Insert(money, 37, 7, 4, x);

		if (x >= 0) {
			entitiesOBJ->Insert(enemy, 51, 7, 4, x);
		}

		if (x >= 1) {
			entitiesOBJ->Insert(enemy, 29, 13, 4, x);
		}

		entitiesOBJ->Insert(money, 53, 13, 4, x);

		if (x >= 2) {
			entitiesOBJ->Insert(enemy, 68, 11, 4, x);
		}

		entitiesOBJ->Insert(powerup, 22, 10, 4, x);

		entitiesOBJ->Insert(money, 42, 5, 5, x);

		if (x >= 2) {
			entitiesOBJ->Insert(enemy, 19, 13, 5, x);
		}

		if (x >= 0) {
			entitiesOBJ->Insert(enemy, 25, 9, 5, x);
		}

		if (x >= 1) {
			entitiesOBJ->Insert(enemy, 49, 8, 5, x);
		}

		entitiesOBJ->Insert(money, 73, 10, 5, x);

		entitiesOBJ->Insert(powerup, 45, 14, 5, x);
	}
}

void Logic::InitMappa(int curmap, int curLev){
	curmap_ = curmap;
	curLev_ = curLev;
	map->leggimappa(curmap);
    map->stampamappa();
}

void Logic::FileWrite(){//scrive il salvataggio su file
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
	myfile<<'x'<<PlayerPointer->pos.x<<'.'<<PlayerPointer->pos.y<<'.'<<'\n';

	ens tmp = entitiesOBJ->ReturnList();
	while(tmp != NULL){
		if(tmp->type!=3){
			myfile<<'_'<<'\n';
		
			myfile<<'t'<<tmp->type<<'\n';

			myfile<<'P'<<tmp->pos.x<<'.'<<tmp->pos.y<<'.'<<'\n';

			myfile<<'m'<<tmp->mappa<<'\n';

			myfile<<'l'<<tmp->livello<<'\n';

			myfile<<'D'<<tmp->death_flag<<'\n';

			myfile<<'x'<<tmp->xForce<<'\n';

			myfile<<'y'<<tmp->yForce<<'\n';
		}

		tmp=tmp->next;
	}

	myfile<<'<';

	myfile.close();
}//considerazioni per il read: dopo ogni valore di counter bot c'è un punto, il death flag è 0 vivo e 1 morto, tra i due valori di position c'è un punto, mi servira aiuto a interpretare il LastMovement del player

void Logic::FileRead(){
	char mychar;
	std::ifstream myfile;
	myfile.open("Salvataggio.txt");
	mychar=myfile.get();//La E
	mychar=myfile.get();//il bool che dice se il file contiene salvataggi o no
	if(mychar == '1' && myfile.good()){

		ReadGeneral();//va bene

		ReadPlayer();

		ReadEntities();
		//ritornare i valori letti/chiamare le funzioni di init da salvataggio
	}
	myfile.close();
}

void Logic::GiveDynamicity()
{
    ens tmp = entitiesOBJ->ReturnList();
	
	UpdateVariables();

	CheckChangeMap();
	
	eventi->PlayerGravity();
	
    while (tmp) {
        if ((!tmp->death_flag) && tmp->mappa == curmap_  && tmp->livello == curLev_ ) {

			DisplayPlayerStats();

			HandleBot(tmp);
			
			collision->ManageCollisions(tmp);

			if(!tmp->death_flag){//questo perche' in ManageCollisions l'entita' potrebbe morire				

            	entitiesOBJ->MoveEntity(tmp);

            	eventi->DecreaseForce(tmp);

           		entitiesOBJ->Display(tmp);
			}
        }
		if(PlayerPointer and InfoPlayer->hp > 0 and PlayerPointer->death_flag){
			PlayerPointer->death_flag = false;
			PlayerPointer->pos.Select(X_PLAYERSPAWN, Y_PLAYERSPAWN);
		}

        tmp = tmp->next;
    }
	entitiesOBJ->RemoveDeadEntities();
    IncrementCounters();
}

int Logic::returnCurMap(){
	return curmap_;
}

int Logic::returnCurLev(){
	return curLev_;
}

void Logic::set_dev_mode(bool on){
	InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();
	Developer_mode = on;
	if(InfoPlayer && on){
		InfoPlayer->colpi = 10000;
		InfoPlayer->hp = 10000;
	}
}

bool Logic::return_DevMode_status(){
	return Developer_mode;
}