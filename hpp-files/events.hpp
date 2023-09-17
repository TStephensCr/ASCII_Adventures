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

	void mvright(int Force);

	void mvleft(int Force);

	void JumpStraight();

	void Jump();

	void Shoot();
public:
	Events(Entities* MyEntities);

	void PlayerGravity();

	void DecreaseForce(ens myEntity);

	int getmv();
};