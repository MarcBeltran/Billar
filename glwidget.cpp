

#include <math.h>
#include <glwidget.h>
#include <QString>


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)

{
    setFocusPolicy( Qt::StrongFocus );
    esc = new Escena();
    xRot = 0;
    yRot = 0;
    zRot = 0;

    a = 20.0;
    h = 20.0;
    p = 20.0;

    up = 0;
    down = 0;
    left = 0;
    right = 0;

    clearColor = Qt::black;
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    program = 0;
    deltaDes = 0.05;
    moviment = false;

}


GLWidget::~GLWidget()
{
    makeCurrent();
    delete esc;
}


// Create a GLSL program object from vertex and fragment shader files
void
GLWidget::InitShader(const char* vShaderFile, const char* fShaderFile)
{           

    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    // Compilació del vertex shader
    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);

    program->bindAttributeLocation("vPosition", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("vColor", PROGRAM_COLOR_ATTRIBUTE);
    // muntatge del shader en el pipeline gràfic per a ser usat
    qDebug()<<program->link();

    // unió del shader al pipeline gràfic

    program->bind();
    esc->camGeneral->toGPU(program);
    program->bind();
}

void GLWidget::initShadersGPU()
{
// Carrega dels shaders i posa a punt per utilitzar els programes carregats a la GPU

   InitShader( "://vshader1.glsl", "://fshader1.glsl" );

}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const

{
    return QSize(400, 400);
}


static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        rotate();
    }
}


void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        rotate();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        rotate();
    }
}


void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    std::cout<<"Estic inicialitzant el shaders"<<std::ends;
    initShadersGPU();

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GLWidget::paintGL()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   esc->camGeneral->toGPU(program);
   esc->draw();
}

void GLWidget::rotate(){
    qNormalizeAngle(xRot);
    qNormalizeAngle(yRot);
    qNormalizeAngle(zRot);

    mat4 transform = ( RotateX( xRot / 16.0 ) *
                        RotateY( yRot / 16.0 ) *
                        RotateZ( zRot / 16.0 ) );

    // A modificar si cal girar tots els objectes
    if (esc->taulaBillar!=NULL) {
        esc->taulaBillar->aplicaTGCentrat(transform);
    }
    if (esc->pla!=NULL) {
        esc->pla->aplicaTGCentrat(transform);
    }
    if (esc->ball!=NULL) {
        esc->ball->aplicaTGCentrat(transform);
    }
    if (esc->conjuntboles!=NULL) {
        esc->conjuntboles->aplicaTGCentrat(transform);
    }
    xRot=0;
    yRot=0;
    zRot=0;
    updateGL();
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#else
    glOrtho(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}

/*
 * Aquest mètode serveix per a calcular si
 * una bola està en col·lisió amb la bola
 * blanca. Retorna 0 en cas negatiu i 1 en cas
 * positiu.
 */


int GLWidget::xoc(vec3 centreBolaBlanca,vec3 centreBola){
    int xoc=0;
    if(esc->conjuntboles!=NULL){
        for(int i = 0;i<15;i++){
            centreBola = esc->conjuntboles->boles[i]->getCentre();
            if(fabs(sqrt((centreBolaBlanca.x-centreBola.x)*(centreBolaBlanca.x-centreBola.x) + (centreBolaBlanca.y-centreBola.y)*(centreBolaBlanca.y-centreBola.y) + (centreBolaBlanca.z-centreBola.z)*(centreBolaBlanca.z-centreBola.z)))<0.17){
                 xoc = 1;
            }
        }
    }
    return xoc;
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    // Metode a implementar
    mat4 t1 = Translate(0,0,-deltaDes);
    mat4 t2 = Translate(0,0,deltaDes);
    mat4 t3 = Translate(-deltaDes,0,0);
    mat4 t4 = Translate(deltaDes,0,0);

    if(esc->ball!=NULL && esc->pla!=NULL){ //En cas de tenir bola blanca i pla
        Capsa3D cBall = esc->ball->calculCapsa3D();
        Capsa3D cPla = esc->pla->calculCapsa3D();
        vec3 centreBolaBlanca = esc->ball->getCentre();
        vec3 centreBola;
        switch ( event->key() )
        {
        case Qt::Key_Up:
            if(up==0){ //Si no hi ha col·lisió
                if (cBall.pmin[2] + cBall.p > cPla.pmin[2] + cPla.p){
                    esc->ball->aplicaTG(t1);
                }
            }
            if(down == 0){ //En cas no col·lisió cap a l'altre sentit
                 up = xoc(centreBolaBlanca,centreBola);
            }
            down = 0;
            break;
        case Qt::Key_Down:
            down = xoc(centreBolaBlanca,centreBola);
            if(down==0){
                if (cBall.pmin[2] < cPla.pmin[2]){
                    esc->ball->aplicaTG(t2);
                }
            }
            if(up == 0){
                 down = xoc(centreBolaBlanca,centreBola);
            }
            up = 0;
            break;
        case Qt::Key_Left:
            if(left==0){
                if (cBall.pmin[0] > cPla.pmin[0]){
                    esc->ball->aplicaTG(t3);
                }
            }
            if(right == 0){
                 left = xoc(centreBolaBlanca,centreBola);
            }
            right = 0;
            break;
        case Qt::Key_Right:
            if(right==0){
                if (cBall.pmin[0] + cBall.a < cPla.pmin[0] + cPla.a){
                    esc->ball->aplicaTG(t4);

                }
            }
            if(left==0){
                right = xoc(centreBolaBlanca,centreBola);
            }
            left = 0;
            break;
        }
        updateGL();
     }

}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    // Metode a implementar en el cas que es mogui la bola

}




void GLWidget::adaptaObjecteTamanyWidget(Objecte *obj)
{
    //Primer calcular la capsa
    mat4 t1 = Translate(-(obj->capsa.pmin[0]+obj->capsa.a/2.0),-(obj->capsa.pmin[1]+obj->capsa.h/2),-(obj->capsa.pmin[2]+obj->capsa.p/2));
    mat4 s = Scale(1/10.0,1/10.0, 1/10.0);
    //partir per la mida maxima de la capsa minima contanidora.
    mat4 t2 = Translate((obj->capsa.pmin[0]+obj->capsa.a/2.0)*0.05,(obj->capsa.pmin[1]+obj->capsa.h/2)*0.05,(obj->capsa.pmin[2]+obj->capsa.p/2)*0.05);
    obj->aplicaTGPoints(t2*s*t1);
}

void GLWidget::newObjecte(Objecte * obj)
{
    //adaptaObjecteTamanyWidget(obj);
    obj->toGPU(program);
    esc->addObjecte(obj);
    qDebug()<<"4";
    updateGL();
}
void GLWidget::newPlaBase()
{
    // Metode que crea un objecte PlaBase poligon amb el punt central al (0,0,0) i perpendicular a Y=0

    // Metode a implementar
    std::cout<<"new Pla base\n";
    plabase *obj;
    obj = new plabase();
    newObjecte(obj);


}

void GLWidget::newObj(QString fichero)
{
    // Metode que carrega un fitxer .obj llegit de disc
    TaulaBillar *obj;
    obj = new TaulaBillar(fichero);
    //adaptaObjecteTamanyWidget(obj);
    obj->toGPUSenseTextures(program);
    esc->addObjecte(obj);

}

void GLWidget::newBola()
{
    std::cout<<"new bola\n";
    bola *obj;
    obj = new bola();
    newObjecte(obj);
}
void GLWidget::newConjuntBoles()
{
    conjuntBoles *obj = new conjuntBoles();
    for(int i = 0;i<15;i++){
        //adaptaObjecteTamanyWidget(obj->boles[i]);
        obj->boles[i]->toGPU(program);
    }
    esc->conjuntboles = obj;

}
void GLWidget::newSalaBillar()
{
    newBola();
    newConjuntBoles();
    newPlaBase();
}

// Metode per iniciar la dinàmica del joc
void GLWidget::Play()
{

}
