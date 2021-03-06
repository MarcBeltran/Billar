#ifndef ESCENA_H
#define ESCENA_H

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>


#include <Common.h>
#include <objecte.h>
#include <taulabillar.h>
#include <plabase.h>
#include <bola.h>
#include <conjuntboles.h>
#include <camera.h>
using namespace std;

class Escena
{
public:
    Escena();
    ~Escena();

    void addObjecte(Objecte *obj);
    void aplicaTG(mat4 m);

    void aplicaTGCentrat(mat4 m);
    void reset();

    void draw();
    void CapsaMinCont3DEscena();

    void iniCamera(bool cam,int ampladaViewport, int alcadaViewport,QGLShaderProgram *program);
    void setAnglesCamera(bool cam, float angX, float angY, float angZ);
    void setVRPCamera(bool cam, point4 vrp);
    void setWindowCamera(bool cam, bool retallat, Capsa2D window);
    void setDCamera(bool cam,float d);

    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    // Objectes de l'escena: a modificar. Ara nomes té un objecte: la taula de billar.
    // Cal afegir la bola blanca o el pla base per testejar o les 15 boles
    TaulaBillar *taulaBillar;
    plabase *pla;
    bola *ball;
    conjuntBoles *conjuntboles;
    Camera *camGeneral;
};

#endif // ESCENA_H
