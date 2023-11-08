#include "hpp-files/Negozio.hpp"
#include <string>

Negozio::Negozio(WINDOW* win,Entities* MyEntities) {
    curwin = win;
    entitiesOBJ = MyEntities;
    InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();
}

void Negozio::create_Shop() {
//coi punti cosa faccio?
    std::string scelte[2]={"ACQUISTA COLPI", "ACQUISTA VITE"};
}

void Negozio::buyshots(){   //10 spari 20 monete?

}

void Negozio::buyLives(){   //10 monete 1 vita -> vita infinita?
    
}


void Negozio::colorPlayer(){   //con 500 punti si puo cambiare colore al player?
std::string colori[4]={"Blue" ,"Green", "Yellow", "Red"};
}


