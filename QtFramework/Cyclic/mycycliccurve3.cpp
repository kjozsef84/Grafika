#include "mycycliccurve3.h"

#include "../Core/Constants.h"

#include <cmath>
#include <iostream>

using namespace std;

namespace cagd {
bicubicSplineArc3::bicubicSplineArc3(GLenum data_usage_flag)
  : LinearCombination3(0.0, 1.0, 4, data_usage_flag){};

GLvoid
bicubicSplineArc3::fillUpPoints()
{

  if (!_is_closed) {

    GLdouble step = 10;

    for (GLuint i = 8; i < _point_count - 8; i++) {
      GLdouble u = (i)*step;
      DCoordinate3& cp = _data[i];
      cp[0] = cos(u);
      cp[1] = sin(u);
      cp[2] = -2.0 + 4.0 * (GLdouble)rand() / (GLdouble)RAND_MAX;
      cout << i << endl;
    }

    _data[7] = _data[10]; // 2
    _data[6] = _data[9];  // 1
    _data[5] = _data[8];  // 0
    _data[4] = _data[8];

    _data[3] = _data[9];
    _data[2] = _data[8];
    _data[1] = _data[8];
    _data[0] = _data[8];

    _data[_point_count - 8] = _data[_point_count - 11];
    _data[_point_count - 7] = _data[_point_count - 10];
    _data[_point_count - 6] = _data[_point_count - 9];
    _data[_point_count - 5] = _data[_point_count - 9];

    _data[_point_count - 4] = _data[_point_count - 10];
    _data[_point_count - 3] = _data[_point_count - 9];
    _data[_point_count - 2] = _data[_point_count - 9];
    _data[_point_count - 1] = _data[_point_count - 9];
  }
}

GLboolean
bicubicSplineArc3::BlendingFunctionValues(GLdouble u,
                                          RowMatrix<GLdouble>& values) const
{

  values.ResizeColumns(4);

  if (u < 0 || u > 1.0)
    return GL_FALSE;

  GLdouble u2 = u * u, u3 = u2 * u;
  GLdouble w1 = 1 - u, w2 = w1 * w1, w3 = w1 * w2;

  values(0) = w3 / 6.0;
  values(1) = (3 * u * w2 + 3 * w1 + 1) / 6;
  values(2) = (3 * u2 * w2 + 3 * u + 1) / 6;
  values(3) = u3 / 6;

  return GL_TRUE;
}

GLboolean
bicubicSplineArc3::CalculateDerivatives(GLuint max_order_of_derivatives,
                                        GLdouble u,
                                        Derivatives& d) const
{

  d.ResizeRows(max_order_of_derivatives + 1);
  d.LoadNullVectors();

  Matrix<GLdouble> dF(max_order_of_derivatives + 1, _data.GetRowCount());

  if (max_order_of_derivatives >= 0) {
    dF(0, 0) = blendingFunction0(u);
    dF(0, 1) = blendingFunction1(u);
    dF(0, 2) = blendingFunction2(u);
    dF(0, 3) = blendingFunction3(u);
  }
  if (max_order_of_derivatives >= 1) {
    dF(1, 0) = blendingFunction0_1(u);
    dF(1, 1) = blendingFunction1_1(u);
    dF(1, 2) = blendingFunction2_1(u);
    dF(1, 3) = blendingFunction3_1(u);
  }
  if (max_order_of_derivatives >= 2) {
    dF(2, 0) = blendingFunction0_2(u);
    dF(2, 1) = blendingFunction1_2(u);
    dF(2, 2) = blendingFunction2_2(u);
    dF(2, 3) = blendingFunction3_2(u);
  }

  for (GLuint r = 0; r <= max_order_of_derivatives; ++r) {

    for (GLuint i = 0; i < _data.GetRowCount(); ++i) {
      d[r] += _data[i] * dF(r, i);
    }
  }

  return GL_TRUE;
}

GLdouble
bicubicSplineArc3::blendingFunction0(GLdouble u) const
{
  GLdouble w1 = 1 - u;
  return (w1 * w1 * w1) / 6;
}

GLdouble
bicubicSplineArc3::blendingFunction1(GLdouble u) const
{
  GLdouble w1 = 1 - u;
  return (3 * w1 * w1 * u + 3 * w1 + 1) / 6;
}

GLdouble
bicubicSplineArc3::blendingFunction2(GLdouble u) const
{
  return blendingFunction1(1 - u);
}

GLdouble
bicubicSplineArc3::blendingFunction3(GLdouble u) const
{
  return blendingFunction0(1 - u);
}

// --------------------------       First Order Derivatives
// ------------------------------------------

GLdouble
bicubicSplineArc3::blendingFunction0_1(GLdouble u) const
{
  GLdouble w1 = 1 - u;
  return (w1 * w1) / -2;
}

GLdouble
bicubicSplineArc3::blendingFunction1_1(GLdouble u) const
{
  GLdouble w1 = 1 - u;
  return (w1 * w1 - 2 * u * w1 - 1) / 2;
}

GLdouble
bicubicSplineArc3::blendingFunction2_1(GLdouble u) const
{
  return -1 * blendingFunction1_1(1 - u);
}

GLdouble
bicubicSplineArc3::blendingFunction3_1(GLdouble u) const
{
  return -1 * blendingFunction0_1(1 - u);
}

// -------------------------------      Second order derivatives
// ----------------------------

GLdouble
bicubicSplineArc3::blendingFunction0_2(GLdouble u) const
{
  return 1 - u;
}

GLdouble
bicubicSplineArc3::blendingFunction1_2(GLdouble u) const
{
  return -2 + 3 * u;
}

GLdouble
bicubicSplineArc3::blendingFunction2_2(GLdouble u) const
{
  // mukodik itt is a szimmetria, csak igy egyszerubb
  return 1 - 3 * u;
}

GLdouble
bicubicSplineArc3::blendingFunction3_2(GLdouble u) const
{
  return u;
}

}
