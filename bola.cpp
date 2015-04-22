#include "bola.h"
#include <math.h>

int id = 0;

/*
 * Constructor de la bola
 * blanca.
 */

bola::bola():Objecte(100000)
{
    v[0] = vec4( 0.0, 0.0, 1.0, 1.0 );
    v[1] = vec4( 0.0, 0.942809, -0.333333, 1.0 );
    v[2] = vec4( -0.816497, -0.471405, -0.333333, 1.0 );
    v[3] = vec4( 0.816497, -0.471405, -0.333333, 1.0 );
    vertex_colors[0] =    color4( 1.0, 1.0, 1.0, 1.0 );
    make();
    initTextura();

    mat4 m = Translate(0, 1.1, -7);
    aplicaTG(m);

}

/*
 * Constructor de les boles de colors.
 * Els arguments t1, t2 i t3 són
 * els paràmetres que passarem a Translate.
 * El paràmetre num és l'identificador de cada
 * bola utilitzat per carregar la textura corresponent.
 */

bola::bola(float t1, float t2, float t3,int num):Objecte(100000)
{
    v[0] = vec4( 0.0, 0.0, 1.0, 1.0 );
    v[1] = vec4( 0.0, 0.942809, -0.333333, 1.0 );
    v[2] = vec4( -0.816497, -0.471405, -0.333333, 1.0 );
    v[3] = vec4( 0.816497, -0.471405, -0.333333, 1.0 );
    vertex_colors[0] =    color4( 1.0, 0.0, 0.0, 1.0 );
    make();

    id = num;
    initTextura();
    mat4 m = Translate(t1, t2, t3);
    aplicaTG(m);
}

void bola::triangle( const point4& a, const point4& b, const point4& c )
{

colors[Index] = vertex_colors[0];
points[Index] = a;
vertexsTextura[Index] = vec2(0.5+atan2(a[2],a[0])/(2*M_PI), 0.5 - asin(a[1])/M_PI);
Index++;
colors[Index] = vertex_colors[0];
points[Index] = b;
vertexsTextura[Index] = vec2(0.5+atan2(b[2],b[0])/(2*M_PI), 0.5 - asin(b[1])/M_PI);
Index++;
colors[Index] = vertex_colors[0];
points[Index] = c;
vertexsTextura[Index] = vec2(0.5+atan2(c[2],c[0])/(2*M_PI), 0.5 - asin(c[1])/M_PI);
Index++;
}

point4 bola::calculVectorUnitari(vec4 c){

    point4 v = c/2.0;
    double normal = sqrt(pow(v[0],2)+pow(v[1],2)+pow(v[2],2));
    v[0] = v[0]/normal;
    v[1] = v[1]/normal;
    v[2] = v[2]/normal;
    v[3] = 1.0;
    return v;

}

void bola::make(){
    Index = 0;
    divide_triangle(v[0], v[1], v[2],1);
    divide_triangle(v[3], v[2], v[1],1);
    divide_triangle(v[0], v[3], v[1],1);
    divide_triangle(v[0], v[2], v[3],1);

}

void bola::divide_triangle(const point4& a,const point4& b,const point4& c, int maxItr){

    if (maxItr < 5){
        point4 v1 = calculVectorUnitari( a + b );
        point4 v2 = calculVectorUnitari( a + c );
        point4 v3 = calculVectorUnitari( b + c );
        divide_triangle(a, v1, v2,maxItr+1);
        divide_triangle(c, v2, v3,maxItr+1);
        divide_triangle(b, v3, v1,maxItr+1);
        divide_triangle(v1, v3, v2,maxItr+1);
    } else {
        triangle(a,b,c);
    }
}
bola::~bola()
{

}

void bola::initTextura()
 {
     qDebug() << "Initializing textures...";
     // Carregar la textura
     glActiveTexture(GL_TEXTURE0);
     char path[30];
     sprintf(path,"://resources/Bola%d.jpg",id);
     qDebug()<<path;
     texture = new QOpenGLTexture(QImage(path));
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::Linear);
     texture->bind(0);
 }

/*
 * Aquest mètodo serveix per a facilitar
 * el càlcul de la distància euclidiana entre
 * boles per a fer el control de col·lisions.
 */

vec3 bola::getCentre(){
    vec3 centre;
    Capsa3D cBall = calculCapsa3D();
    centre[0] = cBall.pmin[0] + cBall.a/2;
    centre[1] = cBall.pmin[1] + cBall.h/2;
    centre[2] = cBall.pmin[2] + cBall.p/2;
    return centre;
}
