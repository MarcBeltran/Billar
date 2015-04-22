#include "conjuntboles.h"


/*
 * Classe per a carregar
 * les 15 boles
 */

conjuntBoles::conjuntBoles()
{
    make();
}

conjuntBoles::~conjuntBoles()
{
    //Omplir això!!!
}

void conjuntBoles::aplicaTGCentrat(mat4 m)
{
    //Falta pa
    for(int i = 0; i<15; i++){
        boles[i]->aplicaTGPoints(m);

    }

}

void conjuntBoles::aplicaTG(mat4 m)
{
    for(int i = 0; i<15; i++){
        boles[i]->aplicaTGPoints(m);
    }
}


/*
 * En aquest mètode carreguem les 15 boles
 * dins d'una graella. Mirar la documentació
 * adjunta.
 */

void conjuntBoles::make(){
        float iX = 1.1;
        float iZ = sqrt(3);
        int count = 1;
        for (int i=0; i<=4; i++){
            for (int j=-i; j<=i; j+=2){
                boles[count-1] = new bola(j*iX, 1.1, 4+i*iZ, count);
                count++;
            }
        }
}

void conjuntBoles::draw(){
    for(int i = 0; i<15; i++){
        boles[i]->draw();
    }
}
