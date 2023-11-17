#define MaxForce 5
#include "Entities.hpp"

class Events
{
protected:
	Entities *entitiesOBJ;

	Player *InfoPlayer;

	WINDOW *curwin;

	ens ListOfEntities;

	ens PlayerPointer = NULL;

private:
	//----Update functions----//
	void UpdateVariables();

	//----Movement functions----//
	void mvright(int Force);
	void mvleft(int Force);
	void JumpStraight();
	void Jump();

	//----Shooting functions----//
	void HandleHitTarget(ens shooter, ens target);
	bool checkIfValidShoot(char obstacle, ens shooter);
	void HandleValidShot(ens shooter, int shooterXPos, int shooterYPos, char lastMovement);

public:
	//----Constructor----//
	Events(Entities *MyEntities);

	//----Player-related functions----//
	void PlayerGravity();
	int getmv();

	//----Entity actions----//
	void Shoot(ens Entity, char Last_movement);
	void DecreaseForce(ens myEntity);
};