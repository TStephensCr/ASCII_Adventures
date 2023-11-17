struct entita
{
  EntityType type;
  MyPosition pos;
  int xForce = 0;
  int yForce = 0;
  bool death_flag = false;
  int mappa = -1;
  int livello = -1;
  entita *next;
};
typedef entita *ens; // e = entit�, n = nello , s = spazio
