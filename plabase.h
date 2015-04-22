#ifndef PLABASE_H
#define PLABASE_H
#include <Common.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <objecte.h>
#include <stdio.h>


const int NumVertices = 6;

typedef vec4  color4;
typedef vec4  point4;

class plabase : public Objecte
{


public:
    plabase();
    void make();
    ~plabase();

private:

    void quad( int a, int b, int c, int d );
    void initTextura();
    point4 vertices[4]; // 8 vertexs del cub
    color4 vertex_colors[4]; // 8 colors RGBA associats a cada vertex

};

#endif // PLABASE_H

