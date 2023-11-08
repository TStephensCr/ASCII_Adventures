#include "hpp-files/Negozio.hpp"

Negozio::Negozio(WINDOW* win,Entities* MyEntities) {
    curwin = win;
    entitiesOBJ = MyEntities;
    InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();
}

void Negozio::create_Shop() {
//coi punti cosa faccio?
   char* scelte[]={"ACQUISTA 1 VITA", "ACQUISTA 10 VITE", "ACQUISTA 1 COLPO", "ACQUISTA 10 COLPI", "ACQUISTA 1 ARMATURA", "ACQUISTA 5 ARMATURE"};

}

void Negozio::buyshots(){   

}

void Negozio::buyLives(){   
    
}




/*

====================================================================================================
|             (  ____ \    (  )    (  )    /         \     (  ____  )                              |
|             | (   \/     |  |    |  |   (    ___    )    | (    ) |                              |
|             | (_____     |  (____)  |   |   /   \   |    | (____) |                              |
|             (_____  )    |   ____   |   |  |     |  |    |  ______)                              |
|                   ) |    |  (    )  |   |   \___/   |    |  |                                    |
|             /\____) |    |  |    |  |   (           )    |  |                                    |
|             \_______)    (__)    (__)    \_________/     (__)                                    |
|                                                                                                  |
|                                                                                                  |
|      ACQUISTA VITE:                  ACQUISTA COLPI                   ACQUISTA ARMATURA:         |
|                                                                                                  |
|    1 vita = 20 monete              1 colpo = 10 monete              1 armatura = 30 monete       |
|                                                                                                  |
|   10 vite =  150 monete           10 colpi = 50 monete              5 armature=  100 monete      |
|                                                                                                  |
|                                                                                                  |
====================================================================================================

*/


