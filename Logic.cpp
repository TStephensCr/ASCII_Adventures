#include "hpp-files/Logic.hpp"

Logic::Logic(WINDOW* win) {

	entitiesOBJ = new Entities(win);

	InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();

	collision = new Collision(entitiesOBJ);

	eventi = new Events(entitiesOBJ);

	Status = Game;

	/*
	----PROVE VARIE CON LE ENTITà----
	
	ens l = entitiesOBJ->Insert(player, 3 , 4);
	ens k = entitiesOBJ->Insert(enemy, 3, 5);
	ens y = entitiesOBJ->Insert(shoot, 3, 6);
	ens t = entitiesOBJ->Insert(money, 3, 7);
	ens p = entitiesOBJ->Insert(enemy, 3, 8);

	k->xForce = 50;
	l->xForce = 100;
	y->xForce = -150;
	t->xForce = 25;
	p->xForce = -25;
	entitiesOBJ->Remove(k);
	entitiesOBJ->Remove(k);
	entitiesOBJ->Remove(l);
	entitiesOBJ->Remove(y);
	entitiesOBJ->Remove(t);
	entitiesOBJ->Remove(p);*/
}

Events *Logic::ReturnEventsOBJ()
{
    return eventi;
}

Entities *Logic::ReturnEntitiesOBJ()
{
    return entitiesOBJ;
}

void Logic::InitEntities(int NumberOfMap = 1){
	entitiesOBJ->Insert(player, X_PLAYERSPAWN , Y_PLAYERSPAWN);
	InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();
}

void Logic::GiveDynamicity()
{
    ens tmp = entitiesOBJ->ReturnList();

	while (tmp) {
		if(!tmp->death_flag){
			entitiesOBJ->ClearPosition(tmp);

			eventi->Gravity(tmp);

			collision->ManageCollisions(tmp);

			entitiesOBJ->MoveEntity(tmp);

			entitiesOBJ->DecreaseForce(tmp);
			
			entitiesOBJ->Display(tmp);
		}

		tmp = tmp->next;
	}
}