#include "hpp-files/Market.hpp"

Negozio::Negozio(WINDOW *win, Entities *MyEntities, Logic *logic_)
{
    curwin = win;
    entitiesOBJ = MyEntities;
    InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();
    logic = logic_;
    // logic = new Logic(win, menuwin);
}
void Negozio::updateVariables()
{
    InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();
}
int Negozio::create_Shop()
{
    int highlight = 0;
    int scelta = 0;

    while (true)
    {
        updateVariables();

        entitiesOBJ->DisplayPlayerStats();

        displayMenu(highlight);

        scelta = wgetch(curwin);
        switch (scelta)
        {
        case KEY_UP:
            highlight = (highlight - 1 + 5) % 5;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % 5;
            break;
        case 10: // Enter
            eventiShop(highlight);
            break;
        case 27:       // Esc
            return -1; // Exit the function
        default:
            break;
        }
    }

    wrefresh(curwin);
    return highlight;
}

void Negozio::displayMenu(int highlight)
{
    const char scelte[] = "|BUY|";
    for (int i = 0; i < 5; i++)
    {
        if (i == highlight)
        {
            wattron(curwin, A_REVERSE);
        }
        mvwprintw(curwin, 1 + (3 * (i + 1)), 3, scelte);
        if (i == highlight)
        {
            wattroff(curwin, A_REVERSE);
        }
    }
}

void Negozio::eventiShop(int scelta)
{
    if (!InfoPlayer)
    {
        return; // Exit if InfoPlayer is nullptr
    }

    switch (scelta)
    {
    case 0:
        if (InfoPlayer->Money <= 0)
        {
            mvwprintw(curwin, 9, 65, "%s", "Non hai abbastanza monete!");
            break;
        }

        if (InfoPlayer->hp <= 80 && InfoPlayer->hp > 0)
        {
            InfoPlayer->hp += 20;
            InfoPlayer->Money -= 1;
        }
        else if (InfoPlayer->hp <= 0)
        {
            mvwprintw(curwin, 9, 55, "%s", "Sei morto! Inizia una nuova partita!");
        }
        else
        {
            mvwprintw(curwin, 9, 65, "%s", "Hai già vita al massimo!");
        }
        break;

    case 1:
        if (InfoPlayer->Money <= 1)
        {
            mvwprintw(curwin, 10, 65, "%s", "Non hai abbastanza monete!");
            break;
        }

        if (InfoPlayer->hp > 0)
        {
            InfoPlayer->colpi += 5;
            InfoPlayer->Money -= 2;
        }
        else
        {
            mvwprintw(curwin, 10, 55, "%s", "Sei morto! Inizia una nuova partita!");
        }
        break;

    case 2:
        if (InfoPlayer->Money <= 2)
        {
            mvwprintw(curwin, 11, 65, "%s", "Non hai abbastanza monete!");
            break;
        }

        if (InfoPlayer->hp > 0)
        {
            InfoPlayer->Money -= 3;
            InfoPlayer->shield = 20;
        }
        else
        {
            mvwprintw(curwin, 11, 55, "%s", "Sei morto! Inizia una nuova partita!");
        }
        break;

    case 3:
        if (InfoPlayer->Money <= 3)
        {
            mvwprintw(curwin, 12, 65, "%s", "Non hai abbastanza monete!");
            break;
        }

        if (InfoPlayer->hp > 0)
        {
            InfoPlayer->Money -= 4;
            logic->increaseMap();
        }
        else
        {
            mvwprintw(curwin, 12, 55, "%s", "Sei morto! Inizia una nuova partita!");
        }
        break;

    case 4:
        if (InfoPlayer->points <= 140)
        {
            mvwprintw(curwin, 13, 65, "%s", "Fai più punti! (150 min.)");
            break;
        }
        if (InfoPlayer->Money <= 4)
        {
            mvwprintw(curwin, 13, 65, "%s", "Non hai abbastanza monete!");
            break;
        }

        if (InfoPlayer->hp > 0)
        {
            InfoPlayer->Money -= 5;
            InfoPlayer->bulletRange += 10;
        }
        else
        {
            mvwprintw(curwin, 13, 55, "%s", "Sei morto! Inizia una nuova partita!");
        }
        break;

    default:
        // Handle other cases
        break;
    }
}
