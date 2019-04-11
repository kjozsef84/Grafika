#pragma once
#include "GLWidget.h"
#include <GL/glu.h>

using namespace std;


namespace cagd
{


    //--------------------------------
    // special and default constructor
    //--------------------------------
    GLWidget::GLWidget(QWidget *parent, const QGLFormat &format): QGLWidget(format, parent)
    {

        _timer = new QTimer(this);
        _timer->setInterval(20);
        connect(_timer,SIGNAL(timeout()),this,SLOT(_animate()));

    }

    GLWidget::~GLWidget(){

        switch (homeworkNumber) {
            case 1:
                for(GLuint i = 0 ; i < _pc_count; i++ ){
                    if (_pc[i])
                      delete _pc[i], _pc[i] = nullptr;
                    if (_img_pc[i])
                        delete _img_pc[i], _img_pc[i] = nullptr;
                }
                break;
        }
           /* case 3:
            cout << "szia" << endl;
                for(GLuint i = 0 ; i < _ps_count; i++ ){
                    if (_ps[i])
                      delete _ps[i], _ps[i] = nullptr;
                    if (_img_ps[i])
                        delete _img_ps[i], _img_ps[i] = nullptr;
                }
                break;
        }*/

        /*if (_pc)
            delete _pc, _pc = nullptr;
        if ( _imageOfPc )
            delete _imageOfPc, _imageOfPc = nullptr;*/
    }

    //--------------------------------------------------------------------------------------
    // this virtual function is called once before the first call to paintGL() or resizeGL()
    //--------------------------------------------------------------------------------------
    void GLWidget::initializeGL()
    {
        // creating a perspective projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = (float)width() / (float)height();
        _z_near = 1.0;
        _z_far = 1000.0;
        _fovy = 45.0;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // setting the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _eye[0] = _eye[1] = 0.0, _eye[2] = 6.0;
        _center[0] = _center[1] = _center[2] = 0.0;
        _up[0] = _up[2] = 0.0, _up[1] = 1.0;

        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

        // enabling the depth test
        glEnable(GL_DEPTH_TEST);

        // setting the background color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // initial values of transformation parameters
        _angle_x = _angle_y = _angle_z = 0.0;
        _trans_x = _trans_y = _trans_z = 0.0;
        _zoom = 1.0;

        try
        {
            // initializing the OpenGL Extension Wrangler library
            GLenum error = glewInit();

            if (error != GLEW_OK)
            {
                throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
            }

            if (!glewIsSupported("GL_VERSION_2_0"))
            {
                throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                                "Try to update your driver or buy a new graphics adapter!");
            }

            // create and store your geometry in display lists or vertex buffer objects
            // ...
        }
        catch (Exception &e)
        {
            cout << e << endl;
        }


        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

     /*   if ( homeworkNumber != 1 ){
           glEnable(GL_LIGHTING);
        }*/
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);

        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glEnable(GL_DEPTH_TEST);

        glewInit();

//------------------------------------------------------------------

        homeworkNumber = 2;

//------------------------------------------------------------------
        switch ( homeworkNumber ) {
            case 1:
                initializeFirst();
                break;
            case 2:
                //glewInit();
                initializeAnimal();
                break;
            case 3:
                initalizeSurface();
                break;
        }


/*
        RowMatrix<ParametricCurve3::Derivative> derivative(3);
        derivative(0) = secondCurve::d0;
        derivative(1) = secondCurve::d1;
        derivative(2) = secondCurve::d2;

        _pc = nullptr;
        _pc = new (nothrow) ParametricCurve3( derivative, secondCurve::u_min, secondCurve::u_max);
        if ( ! _pc ){
            //error
        }
        GLuint pointCount = 300;
        GLenum usage_flag = GL_STATIC_DRAW;

        _imageOfPc = nullptr;
        _imageOfPc = _pc->GenerateImage(pointCount,usage_flag);


        if ( ! _imageOfPc ){
            //error
        }

        if ( ! _imageOfPc -> UpdateVertexBufferObjects(usage_flag) ){
            cout << " error " << endl;
        }
*/



    }

    //-----------------------
    // the rendering function
    //-----------------------
    void GLWidget::paintGL()
    {
        // clears the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // stores/duplicates the original model view matrix
        glPushMatrix();

            // applying transformations
            glRotatef(_angle_x, 1.0, 0.0, 0.0);
            glRotatef(_angle_y, 0.0, 1.0, 0.0);
            glRotatef(_angle_z, 0.0, 0.0, 1.0);
            glTranslated(_trans_x, _trans_y, _trans_z);
            glScaled(_zoom, _zoom, _zoom);

            // render your geometry (this is oldest OpenGL rendering technique, later we will use some advanced methods)


            switch (homeworkNumber) {
                case 1:
                    drawFirst();
                    break;
                case 2:
                    drawAnimal();
                    break;
                case 3:
                    drawSurface();
                    break;
            }

/*
            if (_imageOfPc ){

                glColor3f(1.0f,0.0f,0.0f);
                _imageOfPc->RenderDerivatives(0,GL_LINE_STRIP);
                glPointSize(5.0f);
                    glColor3f(0.0f,0.5f,0.0f);
                    _imageOfPc->RenderDerivatives(1,GL_LINES);
                    _imageOfPc->RenderDerivatives(1,GL_POINTS);

                    glColor3f(0.0f,0.0f,1.0f);
                    _imageOfPc->RenderDerivatives(2,GL_LINES);
                    _imageOfPc->RenderDerivatives(2,GL_LINES);
                glPointSize(1.0f);


            }
            */

/*
            GLuint pointCount = 200, derCount = 1;
            GLfloat du = 4.0 * PI / ( pointCount ), u = -2 * PI;
            Matrix<DCoordinate3> derivatives(derCount+1, pointCount+1);



            for( GLuint i = 0; i <= pointCount; i++ ){
              DCoordinate3 & a =  derivatives(0,i);
              a[0] = u * cos(u);
              a[1] = u* sin(u);
              a[2] = u;

              DCoordinate3 & b =  derivatives(1,i);
              b[0] = cos(u) - u * sin(u);
              b[1] = sin(u) + u * cos(u);
              b[2] = 1;
         5     u+=du;

            }
*/
/*
            for( GLuint i = 0; i < pointCount; i++ ){
              DCoordinate3 & a =  derivatives(1,i);
              a[0] = cos(u) - u * sin(u);
              a[1] = sin(u) + u * cos(u);
              a[2] = 1;
            }
*/

/*
            GenericCurve3 gc3(derivatives,GL_DYNAMIC_DRAW);
            gc3.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW);

            glPointSize(10.0f);
            glColor3f(1.0f,0,0);
            gc3.RenderDerivatives(0,GL_POINTS);
            glColor3f(0.0f,0.0f,1.0f);
            gc3.RenderDerivatives(1,GL_LINES);

            gc3.DeleteVertexBufferObjects();*/
/*
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_LINES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(1.1f, 0.0f, 0.0f);

                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.1f, 0.0f);

                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 0.0f, 1.1f);
            glEnd();

            glBegin(GL_TRIANGLES);
                // attributes
                glColor3f(1.0f, 0.0f, 0.0f);
                // associated with position
                glVertex3f(1.0f, 0.0f, 0.0f);

                // attributes
                glColor3f(0.0, 1.0, 0.0);
                // associated with position
                glVertex3f(0.0, 1.0, 0.0);

                // attributes
                glColor3f(0.0f, 0.0f, 1.0f);
                // associated with position
                glVertex3f(0.0f, 0.0f, 1.0f);
            glEnd();

*/
/*
         GLuint seg_count = 100;
         GLuint vert_count = 2 * seg_count;
         GLfloat color = 1/seg_count;


         GLfloat du = 4.0 * PI / ( vert_count ), u = -2 * PI;


        vector<Vertex> points(vert_count);

        for( vector<Vertex>::iterator it = points.begin(); it < points.end(); ++it){
            it->x =  u * cos(u);
            it->y = u *sin(u);
            it->z = u;
            u+=du;
            cout << u << endl;
        }

        glBegin(GL_LINE_STRIP);
        glColor3i(1,0,0);
        for( vector<Vertex>::iterator it = points.begin(); it < points.end(); ++it ){
            glColor3f(1.0f, 0.0f, 1.0f);
            glVertex3fv(&it->x);
        }

        glEnd();

*/
/*

        GLuint point_count = 200;
        GLuint bufferID, curvePointByteSize = 3 * point_count * sizeof(GLfloat);
        GLfloat * coordinate;
        GLfloat du = 4.0 * PI / ( point_count ), u = -2 * PI;


        glGenBuffers(1, &bufferID);
        if ( ! bufferID ){
            cout << " hiba 1 " << endl;

        }
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ARRAY_BUFFER, curvePointByteSize, 0, GL_DYNAMIC_DRAW);
        coordinate = (GLfloat * ) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

        if ( !coordinate ){
            cout << " hiba 2 " << endl;
        }
        for( GLuint i = 0; i < point_count; i++ ){
            *coordinate = (GLfloat) (u*cos(u));
            coordinate++;

            *coordinate = (GLfloat) (u*sin(u));
            coordinate++;
            *coordinate = (GLfloat) u;
            coordinate++;
             u+=du;
             cout << u << endl;

        }

        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER,0);

        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
            glColor3f(1.0f,0,0);
            glVertexPointer(3, GL_FLOAT, 0, (const GLvoid*)0);
            glDrawArrays(GL_LINE_STRIP, 0, point_count);

            glPointSize(10.0f);
            glColor3f(0.0f,0.0f,1.0f);
            glDrawArrays(GL_POINTS, 0, point_count);

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glDisableClientState(GL_VERTEX_ARRAY);

*/

        // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
        // i.e., the original model view matrix is restored
        glPopMatrix();
    }

    //----------------------------------------------------------------------------
    // when the main window is resized one needs to redefine the projection matrix
    //----------------------------------------------------------------------------
    void GLWidget::resizeGL(int w, int h)
    {
        // setting the new size of the rendering context
        glViewport(0, 0, w, h);

        // redefining the projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = (float)w / (float)h;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // switching back to the model view matrix
        glMatrixMode(GL_MODELVIEW);

        updateGL();
    }

    //-----------------------------------
    // implementation of the public slots
    //-----------------------------------

    void GLWidget::set_angle_x(int value)
    {
        if (_angle_x != value)
        {
            _angle_x = value;
            updateGL();
        }
    }

    void GLWidget::set_angle_y(int value)
    {
        if (_angle_y != value)
        {
            _angle_y = value;
            updateGL();
        }
    }

    void GLWidget::set_angle_z(int value)
    {
        if (_angle_z != value)
        {
            _angle_z = value;
            updateGL();
        }
    }

    void GLWidget::set_zoom_factor(double value)
    {
        if (_zoom != value)
        {
            _zoom = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_x(double value)
    {
        if (_trans_x != value)
        {
            _trans_x = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_y(double value)
    {
        if (_trans_y != value)
        {
            _trans_y = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_z(double value)
    {
        if (_trans_z != value)
        {
            _trans_z = value;
            updateGL();
        }
    }

    void GLWidget::setParametricCurve(int index){
        this->_ps_selected = index;
        //cout << index << endl;
        updateGL();
    }
    void GLWidget::initializeFirst(){


        _pc_count = 5;
        _pointCount = 200;
        _pc.ResizeColumns(_pc_count);

        RowMatrix<ParametricCurve3::Derivative> derivative(3);
        derivative(0) = firstCurve::d0;
        derivative(1) = firstCurve::d1;
        derivative(2) = firstCurve::d2;
        _pc[0] = new ParametricCurve3(derivative, firstCurve::u_min, firstCurve::u_max);

        derivative(0) = secondCurve::d0;
        derivative(1) = secondCurve::d1;
        derivative(2) = secondCurve::d2;
        _pc[1] = new ParametricCurve3(derivative, secondCurve::u_min, secondCurve::u_max);

        derivative(0) = vivianCurve::d0;
        derivative(1) = vivianCurve::d1;
        derivative(2) = vivianCurve::d2;
        _pc[2] = new ParametricCurve3(derivative, vivianCurve::u_min, vivianCurve::u_max);

        derivative(0) = thirdCurve::d0;
        derivative(1) = thirdCurve::d1;
        derivative(2) = thirdCurve::d2;
        _pc[3] = new ParametricCurve3(derivative, thirdCurve::u_min, thirdCurve::u_max);

        derivative(0) = roseCurve::d0;
        derivative(1) = roseCurve::d1;
        derivative(2) = roseCurve::d2;
        _pc[4] = new ParametricCurve3(derivative, roseCurve::u_min, roseCurve::u_max);


        _img_pc.ResizeColumns(_pc_count);
        _scale.ResizeColumns(_pc_count);

        for( GLuint i = 0 ; i < _pc_count; i++ )	//initializa GLMAP
        {
            _scale[i] = 0.5;
            if ( _pc[i] ){
                _img_pc[i] = _pc[i] -> GenerateImage(_pointCount);	//test letezik e a kep vagy se
            }
            if(_img_pc[i]){
                _img_pc[i] -> UpdateVertexBufferObjects(_scale[i]);
            }
        }

        _ps_selected = 0 ;

    }

    void GLWidget::drawFirst(){
        glColor3f(1.0f,0.0f,0.0f);
            _img_pc[_ps_selected]->RenderDerivatives(0,GL_LINE_STRIP);
        glPointSize(5.0f);
            glColor3f(0.0f,0.5f,0.0f);
            _img_pc[_ps_selected]->RenderDerivatives(1,GL_LINES);
            _img_pc[_ps_selected]->RenderDerivatives(1,GL_POINTS);

            glColor3f(0.0f,0.0f,1.0f);
            _img_pc[_ps_selected]->RenderDerivatives(2,GL_LINES);
            _img_pc[_ps_selected]->RenderDerivatives(2,GL_LINES);
        glPointSize(1.0f);

    }

    void GLWidget::initializeAnimal(){

        if ( _animal.LoadFromOFF("Models/mouse.off", true)){
            if(_animal.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)){
                _angle = 0.0;
                _timer->start();
            }
        }
    }
    void GLWidget::drawAnimal(){
          glEnable(GL_LIGHTING);
        MatFBRuby.Apply();
        _animal.Render();
          glDisable(GL_LIGHTING);

    }

    void GLWidget::_animate(){
        GLfloat *vertex = _animal.MapVertexBuffer(GL_READ_WRITE);
        GLfloat *normal = _animal.MapNormalBuffer(GL_READ_ONLY);

        _angle += DEG_TO_RADIAN;
        if( _angle >= TWO_PI)
            _angle -= TWO_PI;

        GLfloat scale = sin(_angle)/3000.0;
        for( GLuint i = 0 ; i < _animal.VertexCount(); i++){
            for (GLuint coordinate = 0; coordinate < 3; coordinate++, vertex++, normal++) {
                *vertex += scale * (*normal);
            }
        }
        set_angle_x(_angle_x + 1);        //radianban varja
        //set_angle_y(_angle_y+1);
        _animal.UnmapVertexBuffer();
        _animal.UnmapNormalBuffer();

        updateGL();
    }


    void GLWidget::initalizeSurface(){
        _ps_count = 5;
        _pointCount = 700;
        _ps.ResizeColumns(_ps_count);

        TriangularMatrix<ParametricSurface3::PartialDerivative> derivative(3);
        derivative(0,0) = firstSurface::d00;
        derivative(1,0) = firstSurface::d10;
        derivative(1,1) = firstSurface::d01;
        _ps[0] = new ParametricSurface3(derivative, firstSurface::u_min, firstSurface::u_max, firstSurface::v_min, firstSurface::v_max);

        derivative(0,0) = secondSurface::d00;
        derivative(1,0) = secondSurface::d10;
        derivative(1,1) = secondSurface::d01;
        _ps[1] = new ParametricSurface3(derivative, secondSurface::u_min, secondSurface::u_max, secondSurface::v_min, secondSurface::v_max);

        derivative(0,0) = thirdSurface::d00;
        derivative(1,0) = thirdSurface::d10;
        derivative(1,1) = thirdSurface::d01;
        _ps[2] = new ParametricSurface3(derivative, thirdSurface::u_min, thirdSurface::u_max, thirdSurface::v_min, thirdSurface::v_max);

        derivative(0,0) = forthSurface::d00;
        derivative(1,0) = forthSurface::d10;
        derivative(1,1) = forthSurface::d01;
        _ps[3] = new ParametricSurface3(derivative, forthSurface::u_min, forthSurface::u_max, forthSurface::v_min, forthSurface::v_max);

        derivative(0,0) = fifthSurface::d00;
        derivative(1,0) = fifthSurface::d10;
        derivative(1,1) = fifthSurface::d01;
        _ps[4] = new ParametricSurface3(derivative, fifthSurface::u_min, fifthSurface::u_max, fifthSurface::v_min, fifthSurface::v_max);

        _img_ps.ResizeColumns(_ps_count);

        for( GLuint i = 0; i < _ps_count; i++ ){
            if ( _ps[i] ){
                _img_ps[i] = _ps[i] -> GenerateImage(_pointCount, _pointCount);	//test letezik e a kep vagy se
            }
            if(_img_ps[i]){
                _img_ps[i] -> UpdateVertexBufferObjects();
            }
        }

        _ps_selected = 0;
    }


    void GLWidget::drawSurface(){
        glEnable(GL_LIGHTING);
        MatFBRuby.Apply();
        _img_ps[_ps_selected]->Render();
          glDisable(GL_LIGHTING);
   }

}

