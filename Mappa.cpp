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

void Mappa::stampamappa(){//deve venire chiamata all'inizio quando una mappa deve apparire, quando il player cambia mappa e anche quando le monete/powerup vengono presi, cosi poi ci possiamo salvare lo stato della mappa senza monete mantenendo 
    int yM;
    int xM;
    for(xM=1;xM<=xMaxG;xM++){
        for(yM=1;yM<=yMaxG;yM++){
            mvwaddch(playwin, yM, xM, Matrice[xM-1][yM-1]);
        }
    }
    return;
}

void Mappa::leggimappa(char curmap){//rimane il fatto che l'apertura del file causa malloc solo quando keypad viene messo a true in finestra menu. pero ho fatto un file semplice che mostra che l'interazione tra keypad e l'apertura del file non da problemi.
    char mychar;
    int i=0;
    int j=-1;
    std::ifstream myfile;
    myfile.open("mockup.mappa.txt");
    if(!myfile.is_open()){
        wgetch(playwin);
        wgetch(playwin);
        wgetch(playwin);
        wgetch(playwin);
    }
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

void Mappa::mapcaller(){//questa deve fare i suoi controlli ogni volta per vedere se chiamare leggimappa o no, e devo decidere se far chiamare stampamappa da questa oppure se metterla nel main diretto
    Mappa::leggimappa('5');
    
}