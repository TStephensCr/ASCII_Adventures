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
    void create_Shop();
    void buyshots();
    void buyLives();
    void colorPlayer();

};

#endif
