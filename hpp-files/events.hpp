#define MaxForce 5
#include "Entities.hpp"


class Events {//Forces Modifier
protected:


	Entities* entitiesOBJ;

	Player* InfoPlayer;

	WINDOW* curwin;

	ens ListOfEntities;

	ens PlayerPointer = NULL;

private:
	void UpdateVariables();
public:


	Events(Entities* MyEntities);

	void mvright(ens myEntity,int Force);

	void mvleft(ens myEntity, int Force);

	void mvdown(ens myEntity);

	void JumpStraight(int Height);

	void Jump(int Height);

	int getmv();

	void Gravity(ens myEntity);
	
};