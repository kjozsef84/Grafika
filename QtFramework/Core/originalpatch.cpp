#include "originalpatch.h"

namespace cagd {

originalPatch::originalPatch(int i, int j)
  : myPatchManager(i, j)
{}

GLvoid
originalPatch::setContolPoints()
{
  DCoordinate3 point;
  GLint n = _net.GetRowCount(), m = _net.GetColumnCount();
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
}

}
