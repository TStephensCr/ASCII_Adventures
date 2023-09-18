#include "hpp-files/Menu.hpp"

Menu:: Menu(WINDOW *win1, WINDOW * win2){
      menuwin = win1;
      inputwin = win2;
      map = new Mappa(inputwin);
}

void Menu::titolo(){
    map->leggimappa(7);
    map->stampamappa();
}

void Menu::GameOver(){
    map->leggimappa(8);
    map->stampamappa();
}


int Menu::finestraMenu(){
      char space = ' ' ;
      int left, right, top, bottom,tlc, trc, blc, brc;
      top = 0;
      left = right= bottom = tlc = trc = blc = brc= (int) space;
      wborder(menuwin,left, right, top, bottom, tlc, trc, blc, brc);

      wrefresh(menuwin);
      
      std::string opzioni[4] = {"NUOVA PARTITA", "CARICA SALVATAGGIO", "NEGOZIO", "ESCI"};
      int highlight=0;
      int scelta=0;

      while(1){
        for(int i=0; i<4; i++){
          if(i==highlight){
            wattron(menuwin, A_REVERSE);//inverte colori
            mvwprintw(menuwin, i+2, 1, opzioni[i].c_str());
            wattroff(menuwin, A_REVERSE);
          }
          else{mvwprintw(menuwin, i+2, 1, opzioni[i].c_str());}
          wrefresh(menuwin);
        }

        scelta= wgetch(menuwin);
        switch(scelta){
          case KEY_UP:
          highlight--;
          if(highlight == -1)
          highlight = 0;
          break;
          case KEY_DOWN:
          highlight++;
          if(highlight == 3)
          highlight = 2;
          break;
          default:
          break;
      }

      //se premo invio
       if (scelta == 10) break;
    }
    
    return highlight;
}



void Menu::finestraGioco(){
    box(inputwin,0,0);
    wrefresh(inputwin);
    
}




