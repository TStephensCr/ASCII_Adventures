#include "Mappa.hpp"
#include <fstream>
#include <iostream>

Mappa::Mappa(WINDOW * win){
    playwin=win;
    keypad(playwin, true);
    for(int xM=0;xM<xMaxG;xM++){
        for(int yM=0;yM<yMaxG;yM++){
            Matrice[xM][yM]=' ';
        }
    }
};

void Mappa::stampamappa(WINDOW * playwin){
    int yM;
    int xM;
    for(xM=1;xM<=xMaxG;xM++){
        for(yM=1;yM<=yMaxG;yM++){
            mvwaddch(playwin, yM, xM, Matrice[xM-1][yM-1]);
        }
    }
    /*mvwaddch(playwin, 2, 42, ' ');
    mvwaddch(playwin,2,41,' ');
    mvwaddch(playwin,2,42,' ');*///sarebbero per la prima mappa(finche troviamo il problema)
    return;
}

void Mappa::leggimappa(char curmap){
    std::ifstream myfile("mockup.mappa.txt");
    char mychar;
    int i=0,j=-1;
    do{
        mychar=myfile.get();}while(mychar!=curmap && myfile.good());

    mychar=myfile.get();

    while(mychar!='1' && mychar!='2' && mychar!='3' && mychar!='4' && mychar!='5' && myfile.good()){
        if(mychar=='\n')
            {j++; i=0; mychar=myfile.get();}
        else{
            Matrice[i][j]=mychar;
            i++;
            mychar=myfile.get();
        }
    }
}
