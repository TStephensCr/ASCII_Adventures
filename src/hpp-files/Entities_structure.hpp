#include "Position.hpp"

struct Entita
{
  EntityType type;
  Position pos;
  int xForce = 0;
  int yForce = 0;
  bool death_flag = false;
  int mappa = -1;
  int livello = -1;
  Entita *next;
};
typedef Entita *entita_p; // e = entit�, n = nello , s = spazio
