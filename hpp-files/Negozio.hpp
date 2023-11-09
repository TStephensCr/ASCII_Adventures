#ifndef NEGOZIO_HPP
#define NEGOZIO_HPP
#include "Entities.hpp"


class Negozio {
protected:
    WINDOW* curwin;
    Entities* entitiesOBJ;
    Player* InfoPlayer;
private:
    void displayMenu(int highlight);
public:
    Negozio(WINDOW* win, Entities* MyEntities);
    void updateVariables();
    int create_Shop();
    void eventiShop(int scelta);
    void buyshots();
    void buyLives();
    void colorPlayer();

};

#endif
