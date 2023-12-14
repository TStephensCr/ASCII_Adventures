#include "../include/Mappa.hpp"
#include <fstream>
#include <iostream>

Mappa::Mappa(WINDOW *win)
{
    playwin = win;
    keypad(playwin, true);

    for (int xM = 0; xM < xMaxG; xM++) // inizializzo la matrice con carattere vuoto
        for (int yM = 0; yM < yMaxG; yM++)
            Matrice[xM][yM] = ' ';
};

void Mappa::stampamappa() // stampo contenuti matrice
{
    int yM;
    int xM;
    for (xM = 1; xM <= xMaxG; xM++)
        for (yM = 1; yM <= yMaxG; yM++)
            mvwaddch(playwin, yM, xM, Matrice[xM - 1][yM - 1]);
}

void Mappa::leggimappa(int curmap) // leggo da file la mappa e la metto in matrice
{
    char mychar;
    int i = 0;
    int j = -1;
    std::ifstream myfile;
    myfile.open("../src/mockup.mappa.txt");

    if (curmap != 10)
    { // se non è la mappa 10(negozio), leggo fino a che non trovo il numero della mappa
        do
        {
            mychar = myfile.get();
        } while ((mychar - '0') != curmap && myfile.good());
    }
    else
    {
        do
        {
            mychar = myfile.get();
        } while (mychar != ';' && myfile.good());
    }

    mychar = myfile.get(); // carattere \n

    bool endWhile = false;
    while (myfile.good() && !endWhile)
    {
        if (std::string("0123456789;").find(mychar) != std::string::npos)
            if (curmap != 10)
                endWhile = true;

        if (!endWhile)
        {
            if (mychar == '\n')
            {
                j++;
                i = 0;
                mychar = myfile.get();
            }
            else
            {
                Matrice[i][j] = mychar;
                i++;
                mychar = myfile.get();
            }
        }
    }
    myfile.close();
}
