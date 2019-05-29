#include "bicubicsplinemanager.h"

#include <iostream>

using namespace std;

namespace cagd {

BicubicSplineManager::BicubicSplineManager(GLuint n, GLboolean isOpen)
{
  this->isOpen = isOpen;
  _point_count = n + 16;
  _n = n;
  bsArcs3.ResizeColumns(_point_count + 1);
  colors.ResizeRows(_point_count + 1);

  for (GLuint i = 0; i <= _point_count; i++) {
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
  GLint index;
  if (isOpen) {
    index = _n - 2;
  } else {
    index = _n + 1;
  }

  for (GLuint i = 1; i <= index; i++) {
    UpdateMyGeometry(i);
    RenderMyGeometry(i);
  }
}

GLvoid
BicubicSplineManager::setBackColor(GLuint _curve_number)
{
  colors[_curve_number - 1].r() = 1.0;
  colors[_curve_number - 1].g() = 0.0;
}

GLvoid
BicubicSplineManager::FillMyGeometry()
{

  GLdouble step = TWO_PI / (_n + 1);
  _points.ResizeRows(_point_count);

  for (GLuint i = 0; i <= _n; i++) {
    GLdouble u = (i)*step;
    DCoordinate3& cp = _points[i];
    cp[0] = cos(u);
    cp[1] = sin(u);
    cp[2] = 0; //-4.0 + 8.0 * (GLdouble)rand() / (GLdouble)RAND_MAX;
  }
}

GLvoid
BicubicSplineManager::ChangeControllPoint(GLuint pointNumber,
                                          DCoordinate3 NewPoint)
{
  if (isOpen)
    ChangeControllPointOpen(pointNumber, NewPoint);
  else {
    ChangeControllPointClosed(pointNumber, NewPoint);
  }
}

GLvoid
BicubicSplineManager::ChangeControllPointOpen(GLint pointNumber,
                                              DCoordinate3 NewPoint)
{
  if (pointNumber <= _point_count) {
    _points[pointNumber] = NewPoint;
    for (GLint j = max(1, pointNumber - 2);
         j <= min((int)_n - 2, pointNumber + 1);
         j++) {
      for (GLint k = -1; k <= 2; k++) {
        bsArcs3[j][k + 1] = _points[j + k];
      }
      UpdateMyGeometry(j);
    }
  }
}
GLvoid
BicubicSplineManager::ChangeControllPointClosed(GLint pointNumber,
                                                DCoordinate3 NewPoint)
{
  _points[pointNumber] = NewPoint;

  if (!pointNumber) {
    for (GLint k = -1; k <= 2; k++) {
      bsArcs3[1][k + 1] = _points[(1 + k) % (_n + 1)];
    }
    for (GLint j = _n - 1; j <= _n + 1; j++) {
      for (GLint k = -1; k <= 2; k++) {
        bsArcs3[j][k + 1] = _points[(j + k) % (_n + 1)];
      }
    }

  } else if (pointNumber == 1) {
    for (GLint j = 1; j <= 2; j++) {
      for (GLint k = -1; k <= 2; k++) {
        bsArcs3[j][k + 1] = _points[(j + k) % (_n + 1)];
      }
    }
    for (GLint j = _n; j <= _n + 1; j++) {
      for (GLint k = -1; k <= 2; k++) {
        bsArcs3[j][k + 1] = _points[(j + k) % (_n + 1)];
      }
    }
  } else if (pointNumber == 2) {
    for (GLint k = -1; k <= 2; k++) {
      bsArcs3[_n + 1][k + 1] = _points[(_n + 1 + k) % (_n + 1)];
    }
    for (GLint j = 1; j <= 3; j++) {
      for (GLint k = -1; k <= 2; k++) {
        bsArcs3[j][k + 1] = _points[(j + k) % (_n + 1)];
      }
    }
  } else {

    GLuint index;
    if (pointNumber <= _point_count) {
      for (GLint j = pointNumber - 2; j <= pointNumber + 1; j++) {
        for (GLint k = -1; k <= 2; k++) {
          bsArcs3[j][k + 1] = _points[(j + k) % (_n + 1)];
        }
      }
    }
  }
}

GLvoid
BicubicSplineManager::UpdateClosed()
{

  for (GLuint i = 1; i <= _n + 2; i++) {
    for (GLint k = -1; k <= 2; k++) {
      bsArcs3[i][k + 1] = _points[(i + k) % (_n + 1)];
    }
  }
}

GLvoid
BicubicSplineManager::UpdateOpen()
{
  for (GLuint i = 1; i <= _n - 2; i++) {
    for (GLint k = -1; k <= 2; k++) {
      bsArcs3[i][k + 1] = _points[i + k];
    }
  }
}

GLvoid
BicubicSplineManager::UpdateMyGeometry(GLuint index)
{
  bsArcs3[index].DeleteVertexBufferObjectsOfData();
  bsArcs3[index].UpdateVertexBufferObjectsOfData();
  _image_of_bsArc3 = bsArcs3[index].GenerateImage(2, 20);

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
  glColor3f(0, 0, 1.0);
  bsArcs3[index].RenderData(GL_LINE_STRIP);
  glColor3f(colors[index].r(), colors[index].g(), colors[index].b());

  if (!_image_of_bsArc3->RenderDerivatives(0, GL_LINE_STRIP)) {
    cout << " Error, the cyclic curve can't be render " << endl;
  }
  /*
  if (index == 5) {

    glColor3f(0, 1, 0);
    if (!_image_of_bsArc3->RenderDerivatives(1, GL_LINES)) {
      cout << " Error, the cyclic curve can't be render " << endl;
    }
    glColor3f(0, 0, 1);
    if (!_image_of_bsArc3->RenderDerivatives(2, GL_LINES)) {
      cout << " Error, the cyclic curve can't be render " << endl;
    }
}
*/
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
  colors[index - 1].g() = 1.0;
}

DCoordinate3
BicubicSplineManager::getPoint(int index)
{
  return _points[index];
}

GLint
BicubicSplineManager::getPointNumber()
{
  return _n;
}

}
