#include "hpp-files/Logic.hpp"

Logic::Logic(WINDOW* win) {

	entitiesOBJ = new Entities(win);

	InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();

	collision = new Collision(entitiesOBJ);

	eventi = new Events(entitiesOBJ);

	Status = Game;
}

Events *Logic::ReturnEventsOBJ()
{
    return eventi;
}

Entities *Logic::ReturnEntitiesOBJ()
{
    return entitiesOBJ;
}
void Logic::GiveDynamicity()
{
    ens tmp = entitiesOBJ->ReturnList();

	while (tmp) {
		entitiesOBJ->ClearPosition(tmp);
		
		eventi->Gravity(tmp);

		collision->ManageCollisions(tmp);

		entitiesOBJ->MoveEntity(tmp);

		entitiesOBJ->DecreaseForce(tmp);
		
		entitiesOBJ->Display(tmp);

		tmp = tmp->next;
	}
}
