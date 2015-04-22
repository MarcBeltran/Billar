#ifndef CONJUNTBOLES_H
#define CONJUNTBOLES_H
#include <bola.h>

class conjuntBoles
{
public:
    void make();
    void aplicaTGCentrat(mat4 m);
    void aplicaTG(mat4 m);
    void draw();
    bola *boles[15];
    conjuntBoles();
    ~conjuntBoles();
};

#endif // CONJUNTBOLES_H
