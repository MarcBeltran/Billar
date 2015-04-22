#ifndef BOLA_H
#define BOLA_H
#include <Common.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <objecte.h>
#include <stdio.h>

typedef vec4  point4;
typedef vec4 color4;

class bola: public Objecte
{
public:
    bola();
    bola(float t1,float t2,float t3,int id);
    vec3 getCentre();
    void make();
    ~bola();
private:
    vec4 v[4];
    color4 vertex_colors[4];

    void triangle(const point4& a, const point4& b, const point4& c);
    void divide_triangle(const point4& a,const point4& b,const point4& c,int maxItr);
    void initTextura();

    point4 calculVectorUnitari(vec4 c);
};


#endif // BOLA_H
