
#include "../Core/Colors4.h"
#include "../Core/Constants.h"
#include "../Core/DCoordinates3.h"
#include "../Core/GenericCurves3.h"
#include "../Core/Matrices.h"
#include "mycycliccurve3.h"
#include <algorithm>

namespace cagd {
class BicubicSplineManager
{
private:
  GLboolean isOpen;
  GLuint _n;
  GLuint _point_count;
  ColumnMatrix<DCoordinate3> _points;
  ColumnMatrix<Color4> colors;
  RowMatrix<bicubicSplineArc3> bsArcs3;
  GenericCurve3* _image_of_bsArc3;
  GLuint selectedPoint = 0;

public:
  BicubicSplineManager(GLuint n, GLboolean isOpen = GL_FALSE);
  GLvoid FillMyGeometry();
  GLvoid UpdateMyGeometry(GLuint index);
  GLvoid RenderMyGeometry(GLuint index);
  GLvoid Update();
  GLvoid Render();
  GLvoid setBackColor(GLuint);
  GLvoid UpdateOpen();
  GLvoid UpdateClosed();
  GLvoid ChangeControllPoint(GLuint pointNumber, DCoordinate3 NewPoint);
  GLvoid ChangeControllPointOpen(GLint pointNumber, DCoordinate3 NewPoint);
  GLvoid highlightCurve(GLuint index);
  GLvoid ChangeControllPointClosed(GLint pointNumber, DCoordinate3 NewPoint);
  GLvoid setIsOpen(GLboolean);
  GLvoid ChangeColor(GLuint pointNumber);
  DCoordinate3 getPoint(int);
  GLint getPointNumber();
};
}
