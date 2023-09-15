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

int Mappa::charToInt(char inputChar) {
    switch (inputChar) {
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        default:
            return 0;
    }
}


void Mappa::leggimappa(int curmap){
    char mychar;
    int i=0;
    int j=-1;
    std::ifstream myfile;
    myfile.open("mockup.mappa.txt");
    do{
        mychar=myfile.get();
    }while(charToInt(mychar)!=curmap && myfile.good());

    mychar=myfile.get();

    while(mychar!='1' && mychar!='2' && mychar!='3' && mychar!='4' && mychar!='5' && mychar!='6' && mychar!='7' && mychar!='8' && mychar!='<' && myfile.good()){
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
