#include "originalpatch.h"

namespace cagd {

originalPatch::originalPatch(int i, int j)
  : myPatchManager(i, j)
{}

GLvoid
originalPatch::setContolPoints( int index )
{
  DCoordinate3 point;
  GLint n = _net.GetRowCount(), m = _net.GetColumnCount();
  if ( index == 0 ) {
  GLdouble uStep = 2.0 / (n - 1), vStep = 2.0 / (m - 1);
  GLdouble u = -1, v = -1;
  for (GLuint i = 0; i < n; i++) {
    for (GLuint j = 0; j < m; j++) {
      point[0] = u;
      point[1] = v;
      point[2] = u * u + v * v;
      _net(i, j) = point;
      v += vStep;
    }
    v = -1;
    u += uStep;
  }
  } else if(index == 1) {
      GLdouble uStep = 3.0 / (n - 1), vStep = TWO_PI / (m - 1);
      GLdouble u = -1, v = -1;
      for (GLuint i = 0; i < n; i++) {
        for (GLuint j = 0; j < m; j++) {
          point[0] = 2 * sin(v);
          point[1] =  2 * cos(v);
          point[2] = u;
          _net(i, j) = point;
          v += vStep;
        }
        v = -1;
        u += uStep;
      }
  } else if ( index == 2 ) {
      GLdouble uStep = PI / (n - 1), vStep = PI / (m - 1);
      GLdouble u = -1, v = -1;
      for (GLuint i = 0; i < n; i++) {
        for (GLuint j = 0; j < m; j++) {
          point[0] = sin(2 * u) * cos(v) * cos(v);
          point[1] =  sin(u) * sin(2 * v) / 2;
          point[2] = cos(2 * u) * cos(v) * cos(v);
          _net(i, j) = point;
          v += vStep;
        }
        v = -1;
        u += uStep;
      }
  }
}

}
