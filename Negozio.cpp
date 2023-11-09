#include "hpp-files/Negozio.hpp"

Negozio::Negozio(WINDOW* win,Entities* MyEntities) {
    curwin = win;
    entitiesOBJ = MyEntities;
    InfoPlayer  = entitiesOBJ->ReturnPlayerOBJ();
}

int Negozio::create_Shop() {
    keypad(curwin, true);
    int xMax, yMax;
    getmaxyx(curwin, yMax, xMax);
    const char scelte[]="|BUY|";
    int highlight=0;
    int scelta=0;
    bool endWhile = false;
    while(!endWhile){
        for(int i=0; i<5; i++){
            if(i==highlight)
                wattron(curwin, A_REVERSE);//inverte colori
            mvwprintw(curwin, 1+(3*(i+1)), 3, scelte);
            if(i==highlight)
                wattroff(curwin, A_REVERSE);
            wrefresh(curwin);
        }
            scelta = wgetch(curwin);
            switch(scelta){
                case KEY_UP:
                    highlight--;
                    if(highlight == -1)
                    highlight = 4;
                    break;
                case KEY_DOWN:
                    highlight++;
                    if(highlight == 5)
                    highlight = 0;
                    break;
                case 10://enter
                    endWhile = true;
                    break;
                case 27://esc
                    endWhile = true;
                    highlight = -1;
                    break;
                default:
                    break;
            }
    }
    wrefresh(curwin);
    return highlight;
}

void Negozio::eventiShop(int scelta){//Questa funzione da segmentation fault, sicuramente per qualche motivo legato alla modifica di InfoPlayer
    switch(scelta){
        case 0://20 hp
            if(InfoPlayer->Money>0){
                InfoPlayer->hp+=20;
                InfoPlayer->Money-=1;
            }
            break;
        case 1:
            if(InfoPlayer->Money>1){
                InfoPlayer->colpi+=5;
                InfoPlayer->Money-=2;
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
     }
}

void Negozio::buyshots(){   
//int hp = 100;
//    int Money = 0;
//  int colpi = 10;
  
}

void Negozio::buyLives(){   
    //int hp = 100;
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


