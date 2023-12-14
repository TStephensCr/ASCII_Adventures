#include "../include/Menu.hpp"

Menu::Menu(WINDOW *win1, WINDOW *win2)
{
  menuwin = win1;
  inputwin = win2;
  map = new Mappa(inputwin);
}

void Menu::titolo()
{
  map->leggimappa(0);
  map->stampamappa();
}

void Menu::GameOver()
{
  map->leggimappa(9);
  map->stampamappa();
  wrefresh(inputwin);
}

int Menu::finestraMenu()
{
  keypad(menuwin, true);
  char space = ' ';
  int left, right, top, bottom, tlc, trc, blc, brc;
  top = 0;
  left = right = bottom = tlc = trc = blc = brc = (int)space;
  wborder(menuwin, left, right, top, bottom, tlc, trc, blc, brc);

  wrefresh(menuwin);

  const char *opzioni[5] = {"NUOVA PARTITA", "CARICA SALVATAGGIO", "NEGOZIO", "ESCI", "PROVA"};
  int highlight = 0;
  int scelta = 0;
  bool endWhile = false;
  while (!endWhile)
  {
    for (int i = 0; i < 5; i++)
    {
      if (i == highlight)
      {
        wattron(menuwin, A_REVERSE); // inverte colori
        mvwprintw(menuwin, i + 2, 1, opzioni[i]);
        wattroff(menuwin, A_REVERSE);
      }
      else
        mvwprintw(menuwin, i + 2, 1, opzioni[i]);
      wrefresh(menuwin);
    }

    scelta = wgetch(menuwin);
    switch (scelta)
    {
    case KEY_UP:
      highlight--;
      if (highlight == -1)
        highlight = 0;
      break;
    case KEY_DOWN:
      highlight++;
      if (highlight == 5)
        highlight = 4;
      break;
    default:
      break;
    }

    // se premo invio
    if (scelta == 10)
      endWhile = true;
  }
  wrefresh(menuwin);
  keypad(menuwin, false);
  return highlight;
}

void Menu::finestraGioco()
{
  box(inputwin, 0, 0);
  wrefresh(inputwin);
}
