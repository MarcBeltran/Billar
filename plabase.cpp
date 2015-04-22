#include "plabase.h"

plabase::plabase() : Objecte(NumVertices)
{
    std::cout<<" antes make\n";

    // Vertices of a unit cube centered at origin, sides aligned with axes
    vertices[0] = point4( 10.0, 0.0, -18.0, 1.0 );
    vertices[1] = point4( -10.0, 0.0, -18.0, 1.0 );
    vertices[2] = point4( -10.0, 0.0, 18.0, 1.0 );
    vertices[3] = point4( 10.0, 0.0, 18.0, 1.0 );

    // RGBA colors
    vertex_colors[0] =    color4( 0.0, 0.0, 0.0, 1.0 );  // black
    vertex_colors[1] =    color4( 1.0, 0.0, 0.0, 1.0 );  // red
    vertex_colors[2] =    color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
    vertex_colors[3] =    color4( 0.0, 1.0, 0.0, 1.0 );  // green
    make();

}

plabase::~plabase()
{

}



// quad generates two triangles for each face and assigns colors
//    to the vertices

void plabase::quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b];
    vertexsTextura[Index] = vec2(1.0, 0.0); Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d];
    vertexsTextura[Index] = vec2(0.0, 1.0); Index++;
}


// Realitzacio de la geometria del cub en una genList o en el vertex array, segons el que visualitzem

void plabase::make()
{
    Index = 0;
    quad( 0, 3, 2, 1 );
    initTextura();
}

void plabase::initTextura()
 {
    // Carregar la textura
    glActiveTexture(GL_TEXTURE0);
    texture = new QOpenGLTexture(QImage("://resources/Fabric_Green_L.jpg"));
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->bind(0);
 }

/*vec3 plabase::vectorNormal(){
   //calculCapsa3D()
}
*/
