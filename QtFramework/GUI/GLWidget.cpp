#pragma once
#include "GLWidget.h"
#include <gl/GLU.h>

using namespace std;

namespace cagd {

//--------------------------------
// special and default constructor
//--------------------------------
GLWidget::GLWidget(QWidget* parent, const QGLFormat& format)
  : QGLWidget(format, parent)
{

  //_timer = new QTimer(this);
  //_timer->setInterval(10);
  // connect(_timer, SIGNAL(timeout()), this, SLOT(_animate()));
  // connect(_timer, SIGNAL(timeout()), this, SLOT(_rotateModel()));
}

GLWidget::~GLWidget()
{

  //  switch (homeworkNumber) {
  //    case 1:
  //      for (GLuint i = 0; i < _pc_count; i++) {
  //        if (_pc[i])
  //          delete _pc[i], _pc[i] = nullptr;
  //        if (_img_pc[i])
  //          delete _img_pc[i], _img_pc[i] = nullptr;
  //      }
  //      break;
  //    case 5:
  //      if (_before_interpolation)
  //        delete _before_interpolation, _before_interpolation = 0;
  //      if (_after_interpolation)
  //        delete _after_interpolation, _after_interpolation = 0;
  //      break;
  //  }

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
// this virtual function is called once before the first call to paintGL() or
// resizeGL()
//--------------------------------------------------------------------------------------
void
GLWidget::initializeGL()
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

  gluLookAt(_eye[0],
            _eye[1],
            _eye[2],
            _center[0],
            _center[1],
            _center[2],
            _up[0],
            _up[1],
            _up[2]);

  // enabling the depth test
  glEnable(GL_DEPTH_TEST);

  // setting the background color
  //  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // initial values of transformation parameters
  _angle_x = _angle_y = _angle_z = 0.0;
  _trans_x = _trans_y = _trans_z = 0.0;
  _zoom = 1.0;

  try {
    // initializing the OpenGL Extension Wrangler library
    GLenum error = glewInit();

    if (error != GLEW_OK) {
      throw Exception(
        "Could not initialize the OpenGL Extension Wrangler Library!");
    }

    if (!glewIsSupported("GL_VERSION_2_0")) {
      throw Exception(
        "Your graphics card is not compatible with OpenGL 2.0+! "
        "Try to update your driver or buy a new graphics adapter!");
    }

    // create and store your geometry in display lists or vertex buffer objects
    // ...
  } catch (Exception& e) {
    cout << e << endl;
  }

  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  //  glEnable(GL_LIGHTING);
  //  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_DEPTH_TEST);

  // glewInit();

  //------------------------------------------------------------------

  homeworkNumber = 1;
  _type_index = 0;
  _combo_index = 0;
  _pc_count = 5;
  _img_pc.ResizeColumns(_pc_count);
  for (GLuint i = 0; i < _pc_count; i++) {
    _img_pc[i] = nullptr;
  }
  _ps_count = 5;
  _img_ps.ResizeColumns(_ps_count);
  for (GLuint i = 0; i < _ps_count; i++) {
    _img_ps[i] = nullptr;
  }
  init_models();
  initializeBicubicSplineArc3();
  initializeMyPatch();
  initializePatchManager();
  set_displayed_image();
  //------------------------------------------------------------------
  //  switch (homeworkNumber) {
  //    case 1:
  //      initialize_parametric_curve(index);
  //      break;
  //    case 2:
  //      initializeModel();
  //      initShader();
  //      break;
  //    case 3:
  //      initalizeSurface();
  //      break;
  //    case 4:
  //      initializeCyclicCurve();
  //      break;
  //    case 5:
  //      initializeBicubicSpline();
  //      break;
  //    case 6:
  //      initializeBicubicSplineArc3();
  //      break;
  //    case 7:
  //      initializePatchManager();
  //      break;
  //    case 8:
  //      initializeMyPatch();
  //      break;
  //  }
}

//-----------------------
// the rendering function
//-----------------------
void
GLWidget::paintGL()
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

  // render your geometry (this is oldest OpenGL rendering technique, later we
  // will use some advanced methods)

  //  switch (homeworkNumber) {
  //    case 1:
  //      drawFirst();
  //      break;
  //    case 2:
  //      drawAnimal();
  //      break;
  //    case 3:
  //      drawSurface();
  //      break;
  //    case 4:
  //      renderCyclicCurve();
  //      break;
  //    case 5:
  //      renderBicubicSpline();
  //      break;
  //    case 6:
  //      renderBicubicSplineArc3();
  //      break;
  //    case 7:
  //      renderPatchManager();
  //      break;
  //    case 8:
  //      renderMyPatch();
  //      break;
  //  }
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

          for( vector<Vertex>::iterator it = points.begin(); it < points.end();
     ++it){ it->x =  u * cos(u); it->y = u *sin(u); it->z = u; u+=du; cout << u
     << endl;
          }

          glBegin(GL_LINE_STRIP);
          glColor3i(1,0,0);
          for( vector<Vertex>::iterator it = points.begin(); it < points.end();
     ++it ){ glColor3f(1.0f, 0.0f, 1.0f); glVertex3fv(&it->x);
          }

          glEnd();

  */
  /*

          GLuint point_count = 200;
          GLuint bufferID, curvePointByteSize = 3 * point_count *
     sizeof(GLfloat); GLfloat * coordinate; GLfloat du = 4.0 * PI / (
     point_count ), u = -2 * PI;


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
  set_displayed_image();
  // pops the current matrix stack, replacing the current matrix with the one
  // below it on the stack, i.e., the original model view matrix is restored
  glPopMatrix();
}

//----------------------------------------------------------------------------
// when the main window is resized one needs to redefine the projection matrix
//----------------------------------------------------------------------------
void
GLWidget::resizeGL(int w, int h)
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
void
GLWidget::set_displayed_image()
{
  //_timer->stop();
  switch (_type_index) {
    case 0:
      switch_parametric_curve(_combo_index);
      show_parametric_curve();
      break;
    case 1:
      switch_parametric_surface(_combo_index);
      show_parametric_surface();
      break;
    case 2:
      show_model();
      break;
    case 3:
      if (!_cyc3) {
        initializeCyclicCurve();
      }
      renderCyclicCurve();
      break;
    case 4:
      if (!_before_interpolation) {
        initializeBicubicSpline();
      }
      renderBicubicSpline();
      break;
    case 5:

      renderBicubicSplineArc3();
      break;
    case 6:
      renderPatchManager();
      break;
    case 7:
      renderMyPatch();
      break;
    default:
      cout << "Something's gone wrong!" << endl;
      exit(1);
  }
}

void
GLWidget::show_parametric_curve()
{
  if (_image_of_pc) {
    glColor3f(1.0f, 0.0f, 0.0f);
    _image_of_pc->RenderDerivatives(0, GL_LINE_STRIP);

    glPointSize(5.0f);
    glColor3f(0.0f, 0.5f, 0.0f);
    _image_of_pc->RenderDerivatives(1, GL_LINES);
    _image_of_pc->RenderDerivatives(1, GL_POINTS);

    glColor3f(0.1f, 0.5f, 0.9f);
    _image_of_pc->RenderDerivatives(2, GL_LINES);
    _image_of_pc->RenderDerivatives(2, GL_POINTS);
    glPointSize(1.0f);
  }
}

void
GLWidget::show_parametric_surface()
{
  //_dl->Enable();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  if (_image_of_ps) {
    MatFBBrass.Apply();
    _image_of_ps->Render();
  }
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  //_dl->Disable();
}

void
GLWidget::show_model()
{
  MatFBBrass.Apply();

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHT0);
  //_dl->Enable();
  switch (_combo_index) {
    case 0:
      _elephant_model.Render();
      break;
    case 1:
      _mouse_model.Render();
      break;
    case 2:
      _sphere_model.Render();
      break;
  }
  //  _dl->Disable();
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  glDisable(GL_NORMALIZE);
}

void
GLWidget::set_angle_x(int value)
{
  if (_angle_x != value) {
    _angle_x = value;
    updateGL();
  }
}

void
GLWidget::set_angle_y(int value)
{
  if (_angle_y != value) {
    _angle_y = value;
    updateGL();
  }
}

void
GLWidget::set_angle_z(int value)
{
  if (_angle_z != value) {
    _angle_z = value;
    updateGL();
  }
}

void
GLWidget::set_zoom_factor(double value)
{
  if (_zoom != value) {
    _zoom = value;
    updateGL();
  }
}

void
GLWidget::set_trans_x(double value)
{
  if (_trans_x != value) {
    _trans_x = value;
    updateGL();
  }
}

void
GLWidget::set_trans_y(double value)
{
  if (_trans_y != value) {
    _trans_y = value;
    updateGL();
  }
}

void
GLWidget::set_trans_z(double value)
{
  if (_trans_z != value) {
    _trans_z = value;
    updateGL();
  }
}

void
GLWidget::initialize_parametric_curve(GLuint index)
{
  RowMatrix<ParametricCurve3::Derivative> derivative(3);
  switch (index) {
    case 0:
      derivative(0) = firstCurve::d0;
      derivative(1) = firstCurve::d1;
      derivative(2) = firstCurve::d2;
      _pc =
        new ParametricCurve3(derivative, firstCurve::u_min, firstCurve::u_max);
      break;
    case 1:
      derivative(0) = secondCurve::d0;
      derivative(1) = secondCurve::d1;
      derivative(2) = secondCurve::d2;
      _pc = new ParametricCurve3(
        derivative, secondCurve::u_min, secondCurve::u_max);
      break;
    case 2:
      derivative(0) = vivianCurve::d0;
      derivative(1) = vivianCurve::d1;
      derivative(2) = vivianCurve::d2;
      _pc = new ParametricCurve3(
        derivative, vivianCurve::u_min, vivianCurve::u_max);
      break;
    case 3:
      derivative(0) = thirdCurve::d0;
      derivative(1) = thirdCurve::d1;
      derivative(2) = thirdCurve::d2;
      _pc =
        new ParametricCurve3(derivative, thirdCurve::u_min, thirdCurve::u_max);
      break;
    case 4:
      derivative(0) = roseCurve::d0;
      derivative(1) = roseCurve::d1;
      derivative(2) = roseCurve::d2;
      _pc =
        new ParametricCurve3(derivative, roseCurve::u_min, roseCurve::u_max);
      break;
    default:
      cout << "No such index!" << endl;
  }
  _scale.ResizeColumns(_pc_count);

  //  for (GLuint i = 0; i < _pc_count; i++) // initializa GLMAP
  //  {
  //    _scale[i] = 0.5;
  //    if (_pc[i]) {
  //      _img_pc[i] =
  //        _pc[i]->GenerateImage(_pointCount); // test letezik e a kep vagy se
  //    }
  //    if (_img_pc[i]) {
  //      _img_pc[i]->UpdateVertexBufferObjects(_scale[i]);
  //    }
  //  }
}

void
GLWidget::switch_parametric_curve(GLuint index)
{
  if (_img_pc[index] == nullptr) {
    initialize_parametric_curve(index);

    GLuint div_point_count = 200;
    GLenum usage_flag = GL_STATIC_DRAW;

    _image_of_pc = nullptr;
    _image_of_pc = _pc->GenerateImage(div_point_count, usage_flag);

    if (!_image_of_pc) {
      // Error
      cout << "Couldn't generate the image!" << endl;
      exit(1);
    }

    _img_pc[index] = _image_of_pc;

    if (!_image_of_pc->UpdateVertexBufferObjects(_scale[index], usage_flag)) {
      cout
        << "Could not create the vertex buffer object of the parametric curve!"
        << endl;
    }
  } else {
    _image_of_pc = _img_pc[index];
  }
}

void
GLWidget::switch_parametric_surface(int index)
{
  if (_img_ps[index] == nullptr) {
    initialize_parametric_surface(index);

    GLuint div_point_count_u = 400;
    GLuint div_point_count_v = 400;
    GLenum usage_flag = GL_STATIC_DRAW;

    _image_of_ps = nullptr;
    _image_of_ps =
      _ps->GenerateImage(div_point_count_u, div_point_count_v, usage_flag);

    if (!_image_of_ps) {
      if (_ps) {
        delete _ps, _ps = nullptr;
      }
      cout << "Could not create image!" << endl;
      // throw Exception("Couldn't create the parametric surface's image.");
    }
    _img_ps[index] = _image_of_ps;
    if (!_image_of_ps->UpdateVertexBufferObjects(usage_flag)) {
      cout << "Could not create the vertex buffer object of the parametric "
              "surface!"
           << endl;
    }
  } else {
    _image_of_ps = _img_ps[index];
  }
}

void
GLWidget::initialize_parametric_surface(int index)
{
  _ps_count = 5;
  _img_ps.ResizeColumns(_ps_count);

  TriangularMatrix<ParametricSurface3::PartialDerivative> derivative(3);
  switch (index) {
    case 0:
      derivative(0, 0) = firstSurface::d00;
      derivative(1, 0) = firstSurface::d10;
      derivative(1, 1) = firstSurface::d01;
      _ps = new ParametricSurface3(derivative,
                                   firstSurface::u_min,
                                   firstSurface::u_max,
                                   firstSurface::v_min,
                                   firstSurface::v_max);
      break;
    case 1:
      derivative(0, 0) = secondSurface::d00;
      derivative(1, 0) = secondSurface::d10;
      derivative(1, 1) = secondSurface::d01;
      _ps = new ParametricSurface3(derivative,
                                   secondSurface::u_min,
                                   secondSurface::u_max,
                                   secondSurface::v_min,
                                   secondSurface::v_max);
      break;
    case 2:
      derivative(0, 0) = thirdSurface::d00;
      derivative(1, 0) = thirdSurface::d10;
      derivative(1, 1) = thirdSurface::d01;
      _ps = new ParametricSurface3(derivative,
                                   thirdSurface::u_min,
                                   thirdSurface::u_max,
                                   thirdSurface::v_min,
                                   thirdSurface::v_max);
      break;
    case 3:
      derivative(0, 0) = forthSurface::d00;
      derivative(1, 0) = forthSurface::d10;
      derivative(1, 1) = forthSurface::d01;
      _ps = new ParametricSurface3(derivative,
                                   forthSurface::u_min,
                                   forthSurface::u_max,
                                   forthSurface::v_min,
                                   forthSurface::v_max);
      break;
    case 4:
      derivative(0, 0) = fifthSurface::d00;
      derivative(1, 0) = fifthSurface::d10;
      derivative(1, 1) = fifthSurface::d01;
      _ps = new ParametricSurface3(derivative,
                                   fifthSurface::u_min,
                                   fifthSurface::u_max,
                                   fifthSurface::v_min,
                                   fifthSurface::v_max);
      break;
  }
  //  _img_ps.ResizeColumns(_ps_count);

  //  for (GLuint i = 0; i < _ps_count; i++) {
  //    if (_ps[i]) {
  //      _img_ps[i] = _ps[i]->GenerateImage(
  //        _pointCount, _pointCount); // test letezik e a kep vagy se
  //    }
  //    if (_img_ps[i]) {
  //      _img_ps[i]->UpdateVertexBufferObjects();
  //    }
  //  }

  //  _ps_selected = 0;
}

void
GLWidget::init_models()
{
  if (_elephant_model.LoadFromOFF("../Models/elephant.off", true)) {
    if (_elephant_model.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
      _angle = 0.0;
      //_timer->start();
    }
  }

  if (_mouse_model.LoadFromOFF("../Models/mouse.off", true)) {
    if (_mouse_model.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
      _angle = 0.0;
      //_timer->start();
    }
  }

  if (_sphere_model.LoadFromOFF("../Models/sphere.off", true)) {
    if (_sphere_model.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
      _angle = 0.0;
      //_timer->start();
    }
  }
}

void
GLWidget::drawSurface()
{
  glEnable(GL_LIGHTING);
  MatFBRuby.Apply();
  _img_ps[_ps_selected]->Render();
  glDisable(GL_LIGHTING);
}

void
GLWidget::initializeCyclicCurve()
{
  GLuint _n = 3;
  _cyc3 = new CyclicCurve3(_n);

  if (!_cyc3) {
    throw("Cannot create a generic curve");
  }
  GLdouble step = TWO_PI / (2 * _n + 1);
  for (GLuint i = 0; i <= 2 * _n; i++) {
    GLdouble u = i * step;
    DCoordinate3& cp = (*_cyc3)[i];
    cp[0] = cos(u);
    cp[1] = sin(u);
    cp[2] = -2.0 + 4.0 * (GLdouble)rand() / (GLdouble)RAND_MAX;
  }

  _cyc3->UpdateVertexBufferObjectsOfData();

  _image_of_cyc3 = _cyc3->GenerateImage(2, 100);

  ColumnMatrix<GLdouble> _knot_vector(2 * _n + 1);
  GLdouble myStep = TWO_PI / _n;
  GLdouble pointValue = 0;

  for (GLuint i = 0; i < 2 * _n + 1; i++) {
    _knot_vector(i) = pointValue;
    pointValue += step;
  }

  ColumnMatrix<DCoordinate3> _dataPointsToInterpolate(2 * _n + 1);

  for (GLuint i = 0; i <= 2 * _n; i++) {
    _dataPointsToInterpolate(i) = (*_cyc3)[i];
  }
  _cyc3->UpdateDataForInterpolation(_knot_vector, _dataPointsToInterpolate);

  _image_of_cyc3_after = _cyc3->GenerateImage(2, 100);

  if (!_image_of_cyc3_after) {
    throw("Cannot create the image of the generic curve, after interpolation");
  }

  if (_image_of_cyc3_after->UpdateVertexBufferObjects()) {
    cout << " Error, cyclic curve, cannot update VBO s, after interpolation"
         << endl;
  }

  if (!_image_of_cyc3) {
    throw("Cannot create the image of the generic curve");
  }
  if (!_image_of_cyc3->UpdateVertexBufferObjects()) {
    cout << " Error, cyclic curve, cannot update VBO s" << endl;
  }
}

void
GLWidget::set_type_index(int index)
{
  _type_index = index;
  _combo_index = 0;
  updateGL();
}

void
GLWidget::set_combo_index(int index)
{
  if (index > -1) {
    _combo_index = index;
    updateGL();
  }
}

void
GLWidget::renderCyclicCurve()
{
  glDisable(GL_LIGHTING);

  glPointSize(10.0f);
  glColor3f(1.0f, 1.0f, 0.0f);
  _cyc3->RenderData(GL_POINTS);
  if (!_image_of_cyc3->RenderDerivatives(0, GL_POINTS)) {
    cout << " Error, the cyclic curve can't be render " << endl;
  }
  glColor3f(1.0, 0.0, 0.0);
  _image_of_cyc3_after->RenderDerivatives(0, GL_LINE_LOOP);
  glPointSize(1.0f);

  glColor3f(0.0f, 0.8f, 1.0f);
  _image_of_cyc3->RenderDerivatives(1, GL_LINES);
  glColor3f(1.0f, 0.8f, 1.0f);
  _image_of_cyc3->RenderDerivatives(2, GL_LINES);
  glPointSize(3.0f);
}

void
GLWidget::initializeBicubicSpline()
{

  glewInit();

  setPatchData();
  _patch.UpdateVertexBufferObjectsOfData();
  _before_interpolation = _patch.GenerateImage(30, 30);
  if (_before_interpolation) {
    _before_interpolation->UpdateVertexBufferObjects();

  } else {
    cout << "Error, the after interpolation is not created ";
  }

  RowMatrix<GLdouble> u_knot_vector(4);
  u_knot_vector(0) = 0.0;
  u_knot_vector(1) = 1.0 / 3.0;
  u_knot_vector(2) = 2.0 / 3.0;
  u_knot_vector(3) = 1.0;

  ColumnMatrix<GLdouble> v_knot_vector(4);
  v_knot_vector(0) = 0.0;
  v_knot_vector(1) = 1.0 / 3.0;
  v_knot_vector(2) = 2.0 / 3.0;
  v_knot_vector(3) = 1.0;

  Matrix<DCoordinate3> data_points_to_interpolate(4, 4);
  for (GLuint row = 0; row < 4; row++) {
    for (GLuint column = 0; column < 4; column++)
      _patch.GetData(row, column, data_points_to_interpolate(row, column));
  }

  if (_patch.UpdateDataForInterpolation(
        u_knot_vector, v_knot_vector, data_points_to_interpolate)) {
    _after_interpolation = _patch.GenerateImage(30, 30);
    if (_after_interpolation) {
      if (!_after_interpolation->UpdateVertexBufferObjects()) {
        cout << " Error, the after interpolation vertexBufferObject was "
                "unsuccesfull"
             << endl;
      }
    } else {
      cout << "Error, the after interpolation is not created ";
    }
  }

  if (uLines) {
    uLines = _patch.GenerateUIsoparametricLines(_ulineCount, 1, 30);
    for (GLuint i = 0; i < _vlineCount; i++) {
      if ((*uLines)[i]) {
        (*uLines)[i]->UpdateVertexBufferObjects(0.2);
      }
    }
  }

  if (vLines) {
    vLines = _patch.GenerateVIsoparametricLines(_vlineCount, 1, 30);
    for (GLuint i = 0; i < _vlineCount; i++) {
      if ((*vLines)[i]) {
        (*vLines)[i]->UpdateVertexBufferObjects(0.2);
      }
    }
  }
}
GLvoid
GLWidget::renderBicubicSpline()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glEnable(GL_LIGHTING);

  if (_before_interpolation) {
    MatFBRuby.Apply();
    if (!_before_interpolation->Render())
      cout << "Error, can't render the before interpolation" << endl;
  } else {
    cout << " Error, before interpolation" << endl;
  }
  /*
  if ( _after_interpolation )
  {

      glEnable(GL_BLEND);
      glDepthMask(GL_FALSE);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);
          MatFBTurquoise.Apply();
          if ( !_after_interpolation ->Render() )
              cout << "Error, can't render the after interpolation " <<
  endl; glDepthMask(GL_TRUE); glDisable(GL_BLEND);
  }
  else {
      cout << " Error, after interpolation " << endl;
  }
  */

  glDisable(GL_LIGHTING);
  glColor3f(0.0, 1.0, 0.0);
  for (GLuint i = 0; i < _ulineCount; i++) {
    if (!(*uLines)[i]->RenderDerivatives(0, GL_LINE_STRIP)) {
      cout << " hiba " << endl;
    } else {
      (*uLines)[i]->RenderDerivatives(1, GL_LINES);
    }
  }

  glColor3f(0.0, 0.0, 1.0);
  for (GLuint i = 0; i < _vlineCount; i++) {
    if (!(*vLines)[i]->RenderDerivatives(0, GL_LINE_STRIP)) {
      cout << " hiba " << endl;
    } else {
      (*vLines)[i]->RenderDerivatives(1, GL_LINES);
    }
  }

  glDisable(GL_LIGHTING);

  glPointSize(5.0f);
  if (!_after_interpolation->Render(GL_POINTS))
    cout << "Error, can't render the after interpolation " << endl;
  glPointSize(1.0f);
  glEnable(GL_LIGHTING);
  glPopMatrix();
}

void
GLWidget::initializeBicubicSplineArc3()
{
  manager = new BicubicSplineManager(10, _open);
  manager->FillMyGeometry();
  _points[0] = _points[1] = _points[2] = 0;
  manager->Update();
}
void
GLWidget::renderBicubicSplineArc3()
{
  glDisable(GL_LIGHTING);
  glPointSize(10.0);
  glBegin(GL_POINTS);
  if (_open && _point_number <= manager->getPointNumber()) {
    DCoordinate3 newPoint = manager->getPoint(_point_number);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(newPoint.x(), newPoint.y(), newPoint.z());
  } else if (!_open && _point_number <= manager->getPointNumber()) {
    DCoordinate3 newPoint = manager->getPoint(_point_number);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(newPoint.x(), newPoint.y(), newPoint.z());
  }
  glEnd();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  manager->Render();
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
}

void
GLWidget::setWhichCurve(int index)
{
  if (index <= manager->getPointNumber() + 2) {
    manager->setBackColor(_curve_number);
    _curve_number = index;
    manager->highlightCurve(index);
    setPoints();
    updateGL();
  }
}

void
GLWidget::setWhichPoint(int index)
{
  _point_number = index;
  setPoints();
  updateGL();
}
void
GLWidget::signalManagement()
{
  manager->ChangeControllPoint(_point_number, _points);
  updateGL();
}

void
GLWidget::setX(double x)
{
  _points[0] = x;
  manager->ChangeControllPoint(_point_number, _points);
  updateGL();
}

void
GLWidget::setY(double y)
{
  _points[1] = y;
  manager->ChangeControllPoint(_point_number, _points);
  updateGL();
}

void
GLWidget::setZ(double z)
{
  _points[2] = z;
  manager->ChangeControllPoint(_point_number, _points);
  updateGL();
}

void
GLWidget::setIsOpen(bool open)
{
  manager->setIsOpen(open);
  manager->Update();
  updateGL();
}
GLvoid
GLWidget::initializePatchManager()
{
  _patchManager = new myPatchManager(10, 10);
  _patchManager->generateImage();
}

GLvoid
GLWidget::renderPatchManager()
{

  paintPoint(_patchManager->getPoint(uIndex, vIndex));
  _patchManager->renderControlPoints();
  _patchManager->renderImages();
}
GLvoid
GLWidget::setPatchData()
{

  _patch.SetData(0, 0, -2, -2, 0);
  _patch.SetData(0, 1, -2, -1, 0);
  _patch.SetData(0, 2, -2, 1, 0);
  _patch.SetData(0, 3, -2, 2, 0);

  _patch.SetData(1, 0, -1, -2, 0);
  _patch.SetData(1, 1, -1, -1, 2);
  _patch.SetData(1, 2, -1, 1, 2);
  _patch.SetData(1, 3, -1, 2, 0);

  _patch.SetData(2, 0, 1, -2, 0);
  _patch.SetData(2, 1, 1, -1, 2);
  _patch.SetData(2, 2, 1, 1, 2);
  _patch.SetData(2, 3, 1, 2, 0);

  _patch.SetData(3, 0, 2, -2, 0);
  _patch.SetData(3, 1, 2, -1, 0);
  _patch.SetData(3, 2, 2, 1, 0);
  _patch.SetData(3, 3, 2, 2, 0);
}
GLvoid
GLWidget::initializeControlNet()
{

  RowMatrix<GLdouble> u_knot_vector(4);
  u_knot_vector(0) = 0.0;
  u_knot_vector(1) = 1.0 / 3.0;
  u_knot_vector(2) = 2.0 / 3.0;
  u_knot_vector(3) = 1.0;

  ColumnMatrix<GLdouble> v_knot_vector(4);
  v_knot_vector(0) = 0.0;
  v_knot_vector(1) = 1.0 / 3.0;
  v_knot_vector(2) = 2.0 / 3.0;
  v_knot_vector(3) = 1.0;

  Matrix<DCoordinate3> data_points_to_interpolate(4, 4);
  for (GLuint row = 0; row < 4; row++) {
    for (GLuint column = 0; column < 4; column++)
      _patch.GetData(row, column, data_points_to_interpolate(row, column));
  }

  if (_patch.UpdateDataForInterpolation(
        u_knot_vector, v_knot_vector, data_points_to_interpolate)) {
    _after_interpolation = _patch.GenerateImage(30, 30);
    if (_after_interpolation) {
      if (!_after_interpolation->UpdateVertexBufferObjects()) {
        cout << " Error, the after interpolation vertexBufferObject was "
                "unsuccesfull"
             << endl;
      }
    } else {
      cout << "Error, the after interpolation is not created ";
    }
    if (!_patch.UpdateVertexBufferObjectsOfData()) {
      cout << "error, cant update patch VBO " << endl;
    }
  }
}
GLvoid
GLWidget::renderControlNet()
{
  glDisable(GL_LIGHTING);
  glPointSize(5.0f);
  glColor3f(1.0, 0.0, 0.0);
  if (!_after_interpolation->Render(GL_POINTS))
    cout << "Error, can't render the after interpolation " << endl;
  glColor3f(0, 1, 0);
  _patch.RenderData();
  glPointSize(1.0f);
  glEnable(GL_LIGHTING);
}

void
GLWidget::initShader()
{
  _selectedShader = 2;
  _shaders.ResizeColumns(4);

  try {
    if (!_shaders[0].InstallShaders("../Shaders/directional_light.vert",
                                    "../Shaders/directional_light.frag")) {
      throw Exception("Directional light failed to load.");
    }

    if (!_shaders[1].InstallShaders("../Shaders/reflection_lines.vert",
                                    "../Shaders/reflection_lines.frag")) {
      throw Exception("Reflection lines failed to load.");
    } else {
      _shaders[1].Enable();
      _shaders[1].SetUniformVariable1f("scale_factor", 4.0f);
      _shaders[1].SetUniformVariable1f("smoothing", 2.0f);
      _shaders[1].SetUniformVariable1f("shading", 1.0f);
      _shaders[1].Disable();
    }

    if (!_shaders[2].InstallShaders("../Shaders/toon.vert",
                                    "../Shaders/toon.frag")) {
      throw Exception("Toon failed to load.");
    }
    {
      _shaders[2].Enable();
      _shaders[2].SetUniformVariable4f(
        "default_outline_color", 1.0f, 1.0f, 1.0f, 1.0f);
      _shaders[2].Disable();
    }

    if (!_shaders[3].InstallShaders("../Shaders/two_sided_lighting.vert",
                                    "../Shaders/two_sided_lighting.frag")) {
      throw Exception("Two sided lighting failed to load.");
    }
  } catch (Exception& e) {
    cerr << e << endl;
  }
}

void
GLWidget::setShaderNumber(int index)
{
  _selectedShader = index;
  updateGL();
}

GLvoid
GLWidget::setPoints()
{

  if (_point_number <= manager->getPointNumber() + 1) {
    DCoordinate3 point = manager->getPoint(_point_number);
    _points[0] = point.x();
    _points[1] = point.y();
    _points[2] = point.z();
    emit xPointChanged(point.x());
    emit yPointChanged(point.y());
    emit zPointChanged(point.z());
  }
}
void
GLWidget::setUIndex(int index)
{
  if (index <= _patchManager->getPointCountU()) {
    uIndex = index;
    DCoordinate3 point = _patchManager->getPoint(uIndex, vIndex);
    patchPoint[0] = point.x();
    patchPoint[1] = point.y();
    patchPoint[2] = point.z();
    emit patchXPointChanged(point.x());
    emit patchYPointChanged(point.y());
    emit patchZPointChanged(point.z());
    updateGL();
  }
}
void
GLWidget::setVIndex(int index)
{
  if (index <= _patchManager->getPointCountV()) {
    vIndex = index;
    DCoordinate3 point = _patchManager->getPoint(uIndex, vIndex);
    patchPoint[0] = point.x();
    patchPoint[1] = point.y();
    patchPoint[2] = point.z();
    emit patchXPointChanged(point.x());
    emit patchYPointChanged(point.y());
    emit patchZPointChanged(point.z());
    updateGL();
  }
}
GLvoid
GLWidget::paintPoint(DCoordinate3 point)
{
  glPointSize(12);
  glDisable(GL_LIGHTING);
  glBegin(GL_POINTS);
  glColor3f(0, 1, 1);
  glVertex3f(point.x(), point.y(), point.z());
  glEnd();
  glEnable(GL_LIGHTING);
  glPointSize(2);
}

void
GLWidget::changePatchPoint()
{
  _patchManager->changeControllPoint(uIndex, vIndex, patchPoint);
  updateGL();
}
void
GLWidget::setPatchX(double x)
{
  patchPoint[0] = x;
  _patchManager->changeControllPoint(uIndex, vIndex, patchPoint);
  updateGL();
}
void
GLWidget::setPatchY(double y)
{
  patchPoint[1] = y;
  _patchManager->changeControllPoint(uIndex, vIndex, patchPoint);
  updateGL();
}
void
GLWidget::setPatchZ(double z)
{
  patchPoint[2] = z;
  _patchManager->changeControllPoint(uIndex, vIndex, patchPoint);
  updateGL();
}

GLvoid
GLWidget::initializeMyPatch()
{
  myOriginalPatch = new originalPatch(10, 10);
  myOriginalPatch->setContolPoints();
  myOriginalPatch->generateImage();
}
GLvoid
GLWidget::renderMyPatch()
{
  myOriginalPatch->renderControlPoints();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  myOriginalPatch->renderImages();
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
}

}
