#include "bicubicsplinemanager.h"

#include <iostream>
using namespace std;

namespace cagd {

BicubicSplineManager::BicubicSplineManager(GLuint n, GLboolean isOpen)
{
  this->isOpen = isOpen;
  _point_count = n + 16;
  _n = n;
  bsArcs3.ResizeColumns(_point_count);
  colors.ResizeRows(_point_count);

  for (GLuint i = 0; i < _point_count; i++) {
    colors[i].r() = 1.0f;
  }
}

GLvoid
BicubicSplineManager::setIsOpen(GLboolean open)
{
  isOpen = open;
}
GLvoid
BicubicSplineManager::Update()
{

  if (isOpen) {
    UpdateOpen();
  } else {
    UpdateClosed();
  }
}

GLvoid
BicubicSplineManager::Render()
{
  for (GLuint i = 0; i <= _n; i++) {
    UpdateMyGeometry(i);
    RenderMyGeometry(i);
  }
}

GLvoid
BicubicSplineManager::setBackColor(GLuint _curve_number)
{
  colors[_curve_number - 1].r() = 1.0;
  colors[_curve_number - 1].b() = 0.0;
}

GLvoid
BicubicSplineManager::FillMyGeometry()
{

  GLdouble step = 10;
  _points.ResizeRows(_point_count);

  for (GLuint i = 0; i < _n; i++) {
    GLdouble u = (i)*step;
    DCoordinate3& cp = _points[i];
    cp[0] = cos(u);
    cp[1] = sin(u);
    cp[2] = -2.0 + 4.0 * (GLdouble)rand() / (GLdouble)RAND_MAX;
  }
}

GLvoid
BicubicSplineManager::ChangeColor(GLuint curveNumber, GLuint pointNumber)
{
  colors[curveNumber + pointNumber - 2].r() = 0.0f;
  colors[curveNumber + pointNumber - 2].b() = 1.0f;
}

GLvoid
BicubicSplineManager::ChangeControllPoint(GLuint curveNumber,
                                          GLuint pointNumber,
                                          DCoordinate3 NewPoint)
{
  ChangeColor(curveNumber, pointNumber);
  if (isOpen)
    ChangeControllPointOpen(curveNumber, pointNumber, NewPoint);
  else {
    ChangeControllPointClosed(curveNumber, pointNumber, NewPoint);
  }
}

GLvoid
BicubicSplineManager::ChangeControllPointOpen(GLuint curveNumber,
                                              GLuint pointNumber,
                                              DCoordinate3 NewPoint)
{

  GLuint originalPoint = curveNumber + pointNumber - 2;
  _points[originalPoint] = NewPoint;

  if (!originalPoint) {
    bsArcs3[0][0] = NewPoint;
    bsArcs3[0][1] = NewPoint;
    bsArcs3[0][2] = NewPoint;
    bsArcs3[0][3] = _points[1];

    bsArcs3[1][0] = NewPoint;
    bsArcs3[1][1] = NewPoint;
    bsArcs3[1][2] = _points[1];
    bsArcs3[1][3] = _points[2];

    bsArcs3[2][0] = NewPoint;
    bsArcs3[2][1] = _points[1];
    bsArcs3[2][2] = _points[2];
    bsArcs3[2][3] = _points[3];

  } else if (originalPoint == 1) {

    bsArcs3[0][0] = _points[0];
    bsArcs3[0][1] = _points[0];
    bsArcs3[0][2] = _points[0];
    bsArcs3[0][3] = NewPoint;

    bsArcs3[1][0] = _points[0];
    bsArcs3[1][1] = _points[0];
    bsArcs3[1][2] = NewPoint;
    bsArcs3[1][3] = _points[2];

    bsArcs3[2][0] = _points[0];
    bsArcs3[2][1] = NewPoint;
    bsArcs3[2][2] = _points[2];
    bsArcs3[2][3] = _points[3];

    bsArcs3[3][0] = NewPoint;
    bsArcs3[3][1] = _points[2];
    bsArcs3[3][2] = _points[3];
    bsArcs3[3][3] = _points[4];

  } else if (originalPoint == _n - 1) {

    bsArcs3[originalPoint - 2][0] = _points[_n - 4];
    bsArcs3[originalPoint - 2][1] = _points[_n - 3];
    bsArcs3[originalPoint - 2][2] = _points[_n - 2];
    bsArcs3[originalPoint - 2][3] = NewPoint;

    bsArcs3[originalPoint - 1][0] = _points[_n - 3];
    bsArcs3[originalPoint - 1][1] = _points[_n - 2];
    bsArcs3[originalPoint - 1][2] = NewPoint;
    bsArcs3[originalPoint - 1][3] = NewPoint;

    bsArcs3[originalPoint][0] = _points[_n - 2];
    bsArcs3[originalPoint][1] = NewPoint;
    bsArcs3[originalPoint][2] = NewPoint;
    bsArcs3[originalPoint][3] = NewPoint;

  } else if (originalPoint == _n - 2) {

    bsArcs3[originalPoint - 2][0] = _points[_n - 5];
    bsArcs3[originalPoint - 2][1] = _points[_n - 4];
    bsArcs3[originalPoint - 2][2] = _points[_n - 3];
    bsArcs3[originalPoint - 2][3] = NewPoint;

    bsArcs3[originalPoint - 1][0] = _points[_n - 4];
    bsArcs3[originalPoint - 1][1] = _points[_n - 3];
    bsArcs3[originalPoint - 1][2] = NewPoint;
    bsArcs3[originalPoint - 1][3] = _points[_n - 1];

    bsArcs3[originalPoint][0] = _points[_n - 3];
    bsArcs3[originalPoint][1] = NewPoint;
    bsArcs3[originalPoint][2] = _points[_n - 1];
    bsArcs3[originalPoint][3] = _points[_n - 1];

    bsArcs3[originalPoint + 1][0] = NewPoint;
    bsArcs3[originalPoint + 1][1] = _points[_n - 1];
    bsArcs3[originalPoint + 1][2] = _points[_n - 1];
    bsArcs3[originalPoint + 1][3] = _points[_n - 1];

  } else {

    GLuint n_1 = _n - 1;
    bsArcs3[originalPoint - 2][0] = _points[originalPoint - 3];
    bsArcs3[originalPoint - 2][1] = _points[originalPoint - 2];
    bsArcs3[originalPoint - 2][2] = _points[originalPoint - 1];
    bsArcs3[originalPoint - 2][3] = NewPoint;

    bsArcs3[originalPoint - 1][0] = _points[originalPoint - 2];
    bsArcs3[originalPoint - 1][1] = _points[originalPoint - 1];
    bsArcs3[originalPoint - 1][2] = NewPoint;
    bsArcs3[originalPoint - 1][3] = _points[(originalPoint + 1) % n_1];

    bsArcs3[originalPoint][0] = _points[originalPoint - 1];
    bsArcs3[originalPoint][1] = NewPoint;
    bsArcs3[originalPoint][2] = _points[(originalPoint + 1) % n_1];
    bsArcs3[originalPoint][3] = _points[(originalPoint + 2) % n_1];

    bsArcs3[originalPoint + 1][0] = NewPoint;
    bsArcs3[originalPoint + 1][1] = _points[(originalPoint + 1) % n_1];
    bsArcs3[originalPoint + 1][2] = _points[(originalPoint + 2) % n_1];
    bsArcs3[originalPoint + 1][3] = _points[(originalPoint + 3) % n_1];
  }
}
GLvoid
BicubicSplineManager::ChangeControllPointClosed(GLuint curveNumber,
                                                GLuint pointNumber,
                                                DCoordinate3 NewPoint)
{
  GLuint originalPoint = curveNumber + pointNumber - 2;
  _points[pointNumber] = NewPoint;

  GLuint n_1 = _n - 1;
  if (!originalPoint) {

    bsArcs3[n_1 - 1][0] = _points[n_1 - 2];
    bsArcs3[n_1 - 1][1] = _points[n_1 - 1];
    bsArcs3[n_1 - 1][2] = _points[n_1];
    bsArcs3[n_1 - 1][3] = NewPoint;

    bsArcs3[n_1][0] = _points[n_1 - 1];
    bsArcs3[n_1][1] = _points[n_1];
    bsArcs3[n_1][2] = NewPoint;
    bsArcs3[n_1][3] = _points[1];

    bsArcs3[_n][0] = _points[n_1 - 1];
    bsArcs3[_n][1] = NewPoint;
    bsArcs3[_n][2] = _points[1];
    bsArcs3[_n][3] = _points[2];

    bsArcs3[0][0] = NewPoint;
    bsArcs3[0][1] = _points[1];
    bsArcs3[0][2] = _points[2];
    bsArcs3[0][3] = _points[3];

  } else if (originalPoint == 1) {

    bsArcs3[_n][0] = _points[4];
    bsArcs3[_n][1] = _points[3];
    bsArcs3[_n][2] = _points[2];
    bsArcs3[_n][3] = NewPoint;

    bsArcs3[0][0] = _points[3];
    bsArcs3[0][1] = _points[2];
    bsArcs3[0][2] = NewPoint;
    bsArcs3[0][3] = _points[0];

    bsArcs3[1][0] = _points[2];
    bsArcs3[1][1] = NewPoint;
    bsArcs3[1][2] = _points[0];
    bsArcs3[1][3] = _points[n_1];

    bsArcs3[2][0] = NewPoint;
    bsArcs3[2][1] = _points[0];
    bsArcs3[2][2] = _points[n_1];
    bsArcs3[2][3] = _points[n_1 - 1];

  } else if (originalPoint == 2) {

    bsArcs3[0][0] = NewPoint;
    bsArcs3[0][1] = _points[1];
    bsArcs3[0][2] = _points[0];
    bsArcs3[0][3] = _points[n_1];

    bsArcs3[1][0] = _points[3];
    bsArcs3[1][1] = NewPoint;
    bsArcs3[1][2] = _points[1];
    bsArcs3[1][3] = _points[0];

    bsArcs3[2][0] = _points[3];
    bsArcs3[2][1] = _points[2];
    bsArcs3[2][2] = NewPoint;
    bsArcs3[2][3] = _points[0];

    bsArcs3[3][0] = NewPoint;
    bsArcs3[3][1] = _points[3];
    bsArcs3[3][2] = _points[4];
    bsArcs3[3][3] = _points[5];

  } else {
    bsArcs3[originalPoint - 2][0] = NewPoint;
    bsArcs3[originalPoint - 2][1] = _points[(originalPoint + 1) % _n];
    bsArcs3[originalPoint - 2][2] = _points[(originalPoint + 2) % _n];
    bsArcs3[originalPoint - 2][3] = _points[(originalPoint + 3) % _n];

    bsArcs3[originalPoint - 1][0] = _points[(originalPoint - 1) % _n];
    bsArcs3[originalPoint - 1][1] = NewPoint;
    bsArcs3[originalPoint - 1][2] = _points[(originalPoint + 1) % _n];
    bsArcs3[originalPoint - 1][3] = _points[(originalPoint + 2) % _n];

    bsArcs3[originalPoint][0] = _points[(originalPoint - 2) % _n];
    bsArcs3[originalPoint][1] = _points[(originalPoint - 1) % _n];
    bsArcs3[originalPoint][2] = NewPoint;
    bsArcs3[originalPoint][3] = _points[(originalPoint + 1) % _n];

    bsArcs3[originalPoint + 1][0] = NewPoint;
    bsArcs3[originalPoint + 1][1] = _points[(originalPoint + 1) % _n];
    bsArcs3[originalPoint + 1][2] = _points[(originalPoint + 2) % _n];
    bsArcs3[originalPoint + 1][3] = _points[(originalPoint + 3) % _n];
  }
}

GLvoid
BicubicSplineManager::UpdateClosed()
{

  GLuint aux = _n - 1;
  for (GLuint i = 0; i <= _n; i++) {

    bsArcs3[i][0] = _points[(i % aux)];
    bsArcs3[i][1] = _points[((i + 1) % aux)];
    bsArcs3[i][2] = _points[((i + 2) % aux)];
    bsArcs3[i][3] = _points[((i + 3) % aux)];
  }
}

GLvoid
BicubicSplineManager::UpdateOpen()
{

  bsArcs3[0][0] = _points[0];
  bsArcs3[0][1] = _points[0];
  bsArcs3[0][2] = _points[0];
  bsArcs3[0][3] = _points[1];

  bsArcs3[1][0] = _points[0];
  bsArcs3[1][1] = _points[0];
  bsArcs3[1][2] = _points[1];
  bsArcs3[1][3] = _points[2];

  // --------     orriginal points
  GLuint index = 0;
  for (GLuint i = 2; i <= _n - 2; i++) {

    (bsArcs3[i])[0] = _points[index];
    (bsArcs3[i])[1] = _points[index + 1];
    (bsArcs3[i])[2] = _points[index + 2];
    (bsArcs3[i])[3] = _points[index + 3];

    index++;
  }

  //  ------ END  --------------------

  bsArcs3[_n - 1][0] = _points[_n - 3];
  bsArcs3[_n - 1][1] = _points[_n - 2];
  bsArcs3[_n - 1][2] = _points[_n - 1];
  bsArcs3[_n - 1][3] = _points[_n - 1];

  bsArcs3[_n][0] = _points[_n - 2];
  bsArcs3[_n][1] = _points[_n - 1];
  bsArcs3[_n][2] = _points[_n - 1];
  bsArcs3[_n][3] = _points[_n - 1];
}

GLvoid
BicubicSplineManager::UpdateMyGeometry(GLuint index)
{
  bsArcs3[index].UpdateVertexBufferObjectsOfData();
  _image_of_bsArc3 = bsArcs3[index].GenerateImage(2, 400);

  if (!_image_of_bsArc3) {
    throw("Cannot create the image of my generic curve");
  }
  if (!_image_of_bsArc3->UpdateVertexBufferObjects()) {
    cout << " Error, mycyclic curve, cannot update VBO s" << endl;
  }
}

GLvoid
BicubicSplineManager::RenderMyGeometry(GLuint index)
{
  glDisable(GL_LIGHTING);

  glPointSize(10.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  bsArcs3[index].RenderData(GL_POINTS);
  glColor3f(colors[index].r(), colors[index].g(), colors[index].b());
  if (!_image_of_bsArc3->RenderDerivatives(0, GL_LINE_STRIP)) {
    cout << " Error, the cyclic curve can't be render " << endl;
  }
  glPointSize(1.0f);

  /*
          glColor3f(0.0f,0.8f,1.0f);
          _image_of_bsArc3->RenderDerivatives(1,GL_LINES);
          glColor3f(1.0f,0.8f,1.0f);
          _image_of_bsArc3->RenderDerivatives(2,GL_LINES);
          glPointSize(3.0f);
  */
}

GLvoid
BicubicSplineManager::highlightCurve(GLuint index)
{
  colors[index - 1].r() = 0.0;
  colors[index - 1].b() = 1.0;
}

}
