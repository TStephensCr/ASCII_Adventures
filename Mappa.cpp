#include "hpp-files/Mappa.hpp"
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

void Mappa::stampamappa(){//deve venire chiamata all'inizio quando una mappa deve apparire e quando il player cambia mappa  
    int yM;
    int xM;
    for(xM=1;xM<=xMaxG;xM++){
        for(yM=1;yM<=yMaxG;yM++){
            mvwaddch(playwin, yM, xM, Matrice[xM-1][yM-1]);
        }
    }
    return;
}

void Mappa::leggimappa(char curmap){
    char mychar;
    int i=0;
    int j=-1;
    std::ifstream myfile;
    myfile.open("mockup.mappa.txt");
    do{
        mychar=myfile.get();}while(mychar!=curmap && myfile.good());

    mychar=myfile.get();

    while(mychar!='1' && mychar!='2' && mychar!='3' && mychar!='4' && mychar!='5' && mychar!='M' && myfile.good()){
        if(mychar=='\n')
            {j++; i=0; mychar=myfile.get();}
        else{
            Matrice[i][j]=mychar;
            i++;
            mychar=myfile.get();
        }
    }
    myfile.close();
}

void Mappa::mapcaller(char curmap){//questa deve fare i suoi controlli ogni volta per vedere se chiamare leggimappa o no, e devo decidere se far chiamare stampamappa da questa oppure se metterla nel main diretto
    Mappa::leggimappa(curmap);
    
}
