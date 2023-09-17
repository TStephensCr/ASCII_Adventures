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

void Logic::FileSave(){
	char mychar;
	std::ofstream myfile;
	myfile.open("Salvataggio.txt");
	myfile.put('A');
	myfile.close();
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