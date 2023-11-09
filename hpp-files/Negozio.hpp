#ifndef NEGOZIO_HPP
#define NEGOZIO_HPP
#include "Entities.hpp"


class Negozio {
protected:
    WINDOW* curwin;
    Entities* entitiesOBJ;
    Player* InfoPlayer;
public:
    Negozio(WINDOW* win, Entities* MyEntities);
    int create_Shop();
    void eventiShop(int scelta);
    void buyshots();
    void buyLives();
    void colorPlayer();

};

#endif
