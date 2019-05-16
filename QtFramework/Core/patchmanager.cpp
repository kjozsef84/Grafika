#include "patchmanager.h"

namespace cagd {

patchManager::patchManager()
{
  _data = Matrix<DCoordinate3>(4, 4);
  patches.ResizeColumns(_patchCount);
  _imageOfPatches.ResizeColumns(_patchCount);
}

GLvoid
patchManager::setContolPoints(BicubicBSplinePatch& _patch)
{
  // first the original
  patches(0).SetData(0, 0, _data(0, 0));
  patches(0).SetData(0, 1, _data(0, 1));
  patches(0).SetData(0, 2, _data(0, 2));
  patches(0).SetData(0, 3, _data(0, 3));

  patches(0).SetData(1, 0, _data(1, 0));
  patches(0).SetData(1, 1, _data(1, 1));
  patches(0).SetData(1, 2, _data(1, 2));
  patches(0).SetData(1, 3, _data(1, 3));

  patches(0).SetData(2, 0, _data(2, 0));
  patches(0).SetData(2, 1, _data(2, 1));
  patches(0).SetData(2, 2, _data(2, 2));
  patches(0).SetData(2, 3, _data(2, 3));

  patches(0).SetData(3, 0, _data(3, 0));
  patches(0).SetData(3, 1, _data(3, 1));
  patches(0).SetData(3, 2, _data(3, 2));
  patches(0).SetData(3, 3, _data(3, 3));

  // second UP

  patches(1).SetData(0, 0, _data(0, 0));
  patches(1).SetData(0, 1, _data(0, 1));
  patches(1).SetData(0, 2, _data(0, 2));
  patches(1).SetData(0, 3, _data(0, 3));

  patches(1).SetData(1, 0, _data(0, 0));
  patches(1).SetData(1, 1, _data(0, 1));
  patches(1).SetData(1, 2, _data(0, 2));
  patches(1).SetData(1, 3, _data(0, 3));

  patches(1).SetData(2, 0, _data(1, 0));
  patches(1).SetData(2, 1, _data(1, 1));
  patches(1).SetData(2, 2, _data(1, 2));
  patches(1).SetData(2, 3, _data(1, 3));

  patches(1).SetData(3, 0, _data(2, 0));
  patches(1).SetData(3, 1, _data(2, 1));
  patches(1).SetData(3, 2, _data(2, 2));
  patches(1).SetData(3, 3, _data(2, 3));
}

GLvoid
patchManager::generateImages()
{
  for (GLuint i = 0; i < _patchCount; i++) {
    _imageOfPatches[i] = patches[i].GenerateImage(30, 30);
  }
}

GLvoid
patchManager::renderImages()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glEnable(GL_LIGHTING);

  if (_imageOfPatches[0]) {
    MatFBRuby.Apply();
    if (!_imageOfPatches[0]->Render())
      cout << "Error, can't render the before interpolation" << endl;
  } else {
    cout << " Error, before interpolation" << endl;
  }
}

GLvoid
patchManager::getData(BicubicBSplinePatch& _patch)
{
  for (GLuint i = 0; i < 4; i++) {
    for (GLuint j = 0; j < 4; j++) {
      _patch.GetData(i, j, _data(i, j));
    }
  }
}

}
