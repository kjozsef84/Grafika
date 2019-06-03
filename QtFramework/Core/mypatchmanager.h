#include "../Core/Constants.h"
#include "../Core/DCoordinates3.h"
#include "../Core/Materials.h"
#include "../Core/Matrices.h"
#include "../Core/bicubicbsplinepatch.h"
#include <algorithm>

using namespace std;

namespace cagd {

class myPatchManager
{
protected:
  Matrix<DCoordinate3> _net;
  GLuint _size = 4;
  Matrix<BicubicBSplinePatch> patches;
  Matrix<TriangulatedMesh3*> _imageOfPatches;
  GLuint _patchCount = 9;
  GLuint rowCount, columnCount;

public:
  myPatchManager(int, int);
  ~myPatchManager();
  GLvoid generateImage();
  GLvoid generateImageAux();
  GLvoid renderImages();
  GLvoid renderControlPoints();
  DCoordinate3 getPoint(int, int);
  GLint getPointCountU();
  GLint getPointCountV();
  GLvoid changeControllPoint(int, int, DCoordinate3);
  GLvoid setControlPoint(int, int, DCoordinate3);
};
}
