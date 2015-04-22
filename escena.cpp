#include "escena.h"

Escena::Escena()
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;
    pla = NULL;
    taulaBillar = NULL;
    ball = NULL;
    conjuntboles = NULL;
    camGeneral = new Camera();

}

Escena::~Escena()
{

    // Cal anar fent delete dels objectes que se'l hagi fet new
   delete this->taulaBillar;
   delete this->pla;
    delete this->ball;
    delete this->conjuntboles;
}

void Escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<TaulaBillar*>(obj))
        this->taulaBillar = (TaulaBillar*)obj;
    if (dynamic_cast<plabase*>(obj))
        this->pla = (plabase*)obj;
    if (dynamic_cast<bola*>(obj))
        this->ball = (bola*)obj;
}


void Escena::CapsaMinCont3DEscena()
{

}

void Escena::aplicaTG(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTG(m);
    if (pla!=NULL)
        pla->aplicaTG(m);
    if (ball!=NULL)
        ball->aplicaTG(m);
    if(conjuntboles!=NULL)
        conjuntboles->aplicaTG(m);

}

void Escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTGCentrat(m);
    if(pla!=NULL)
        pla->aplicaTGCentrat(m);
    if(ball!=NULL)
        ball->aplicaTGCentrat(m);
    if(conjuntboles!=NULL)
        conjuntboles->aplicaTGCentrat(m);

}

void Escena::draw() {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->drawSenseTextures();
    if (pla!=NULL)
        pla->draw();
    if (ball!=NULL)
        ball->draw();
    if(conjuntboles!=NULL)
        conjuntboles->draw();
}

void Escena::iniCamera(bool camGeneral,int ampladaViewport, int alcadaViewport, QGLShaderProgram *program){
    if(camGeneral){
        this->camGeneral->ini(ampladaViewport,alcadaViewport,capsaMinima);
        point4 p = vec4(0,0,0,1);
        this->camGeneral->vs.obs = vec4(0,20,0,1);
        this->camGeneral->vs.vup = vec4(0,0,1,0);
        setVRPCamera(1,p);
        this->camGeneral->program = program;
        this->camGeneral->toGPU(program);
    }
}

void Escena::setAnglesCamera(bool camGeneral, float angX, float angY, float angZ){
    if(camGeneral){
        this->camGeneral->CalculVup(angX,angY,angZ);
    }
}

void Escena::setVRPCamera(bool camGeneral, point4 vrp){
    if(camGeneral){
        this->camGeneral->vs.vrp = vrp;
        this->camGeneral->piram.d = length(this->camGeneral->vs.obs - vrp);
    }
}

void Escena::setWindowCamera(bool camGeneral, bool retallat, Capsa2D window){
    if(camGeneral){
        if(retallat){
            this->camGeneral->CalculWindowAmbRetallat();
        } else {
            this->camGeneral->wd = window;
        }
    }
}

void Escena::setDCamera(bool camGeneral,float d){
    if(camGeneral){
        this->camGeneral->piram.d = d;
        this->camGeneral->vs.obs=this->camGeneral->CalculObs(this->camGeneral->vs.vrp,d,this->camGeneral->vs.angx,this->camGeneral->vs.angy);
    }
}



