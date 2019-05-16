#pragma once

#include "../Core/DCoordinates3.h"
#include "../Core/Materials.h"
#include "../Core/Matrices.h"
#include "../Core/bicubicbsplinepatch.h"

using namespace std;

namespace cagd {

class patchManager
{
private:
  Matrix<DCoordinate3> _data;
  GLuint _size = 4;
  RowMatrix<BicubicBSplinePatch> patches;
  RowMatrix<TriangulatedMesh3*> _imageOfPatches;
  GLuint _patchCount = 9;

public:
  patchManager();
  GLvoid setContolPoints(BicubicBSplinePatch&);
  GLvoid getData(BicubicBSplinePatch&);
  GLvoid generateImages();
  GLvoid renderImages();
};
}
