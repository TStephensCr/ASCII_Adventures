struct entita {
  EntityType type;
  Position* pos = new Position();
  int xForce = 0;
  int yForce = 0;
  entita* next;
};
typedef entita* ens;  // e = entit�, n = nello , s = spazio