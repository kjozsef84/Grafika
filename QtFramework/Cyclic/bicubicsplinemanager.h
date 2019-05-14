
#include "../Core/Colors4.h"
#include "../Core/DCoordinates3.h"
#include "../Core/GenericCurves3.h"
#include "../Core/Matrices.h"
#include "mycycliccurve3.h"

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
  GLvoid ChangeControllPoint(GLuint curveNumber,
                             GLuint pointNumber,
                             DCoordinate3 NewPoint);
  GLvoid ChangeControllPointOpen(GLuint curveNumber,
                                 GLuint pointNumber,
                                 DCoordinate3 NewPoint);
  GLvoid highlightCurve(GLuint index);
  GLvoid ChangeControllPointClosed(GLuint curveNumber,
                                   GLuint pointNumber,
                                   DCoordinate3 NewPoint);
  GLvoid setIsOpen(GLboolean);
  GLvoid ChangeColor(GLuint curveNumber, GLuint pointNumber);
};
}
