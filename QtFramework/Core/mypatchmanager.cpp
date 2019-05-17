#include "myPatchManager.h"

namespace cagd {

myPatchManager::myPatchManager()
{
  _data = Matrix<DCoordinate3>(4, 4);
  patches.ResizeColumns(_patchCount);
}

GLvoid
myPatchManager::setContolPoints()
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

  // UP

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

  // LEFT

  patches(2).SetData(0, 0, _data(0, 0));
  patches(2).SetData(0, 1, _data(0, 0));
  patches(2).SetData(0, 2, _data(0, 1));
  patches(2).SetData(0, 3, _data(0, 2));

  patches(2).SetData(1, 0, _data(1, 0));
  patches(2).SetData(1, 1, _data(1, 0));
  patches(2).SetData(1, 2, _data(1, 1));
  patches(2).SetData(1, 3, _data(1, 2));

  patches(2).SetData(2, 0, _data(2, 0));
  patches(2).SetData(2, 1, _data(2, 0));
  patches(2).SetData(2, 2, _data(2, 1));
  patches(2).SetData(2, 3, _data(2, 2));

  patches(2).SetData(3, 0, _data(3, 0));
  patches(2).SetData(3, 1, _data(3, 0));
  patches(2).SetData(3, 2, _data(3, 1));
  patches(2).SetData(3, 3, _data(3, 2));

  // RIGHT

  patches(3).SetData(0, 0, _data(0, 1));
  patches(3).SetData(0, 1, _data(0, 2));
  patches(3).SetData(0, 2, _data(0, 3));
  patches(3).SetData(0, 3, _data(0, 3));

  patches(3).SetData(1, 0, _data(1, 1));
  patches(3).SetData(1, 1, _data(1, 2));
  patches(3).SetData(1, 2, _data(1, 3));
  patches(3).SetData(1, 3, _data(1, 3));

  patches(3).SetData(2, 0, _data(2, 1));
  patches(3).SetData(2, 1, _data(2, 2));
  patches(3).SetData(2, 2, _data(2, 3));
  patches(3).SetData(2, 3, _data(2, 3));

  patches(3).SetData(3, 0, _data(3, 1));
  patches(3).SetData(3, 1, _data(3, 2));
  patches(3).SetData(3, 2, _data(3, 3));
  patches(3).SetData(3, 3, _data(3, 3));

  // DOWN

  patches(4).SetData(0, 0, _data(1, 0));
  patches(4).SetData(0, 1, _data(1, 1));
  patches(4).SetData(0, 2, _data(1, 2));
  patches(4).SetData(0, 3, _data(1, 3));

  patches(4).SetData(1, 0, _data(2, 0));
  patches(4).SetData(1, 1, _data(2, 1));
  patches(4).SetData(1, 2, _data(2, 2));
  patches(4).SetData(1, 3, _data(2, 3));

  patches(4).SetData(2, 0, _data(3, 0));
  patches(4).SetData(2, 1, _data(3, 1));
  patches(4).SetData(2, 2, _data(3, 2));
  patches(4).SetData(2, 3, _data(3, 3));

  patches(4).SetData(3, 0, _data(3, 0));
  patches(4).SetData(3, 1, _data(3, 1));
  patches(4).SetData(3, 2, _data(3, 2));
  patches(4).SetData(3, 3, _data(3, 3));

  // UP-RIGHT

  patches(5).SetData(0, 0, _data(0, 1));
  patches(5).SetData(0, 1, _data(0, 2));
  patches(5).SetData(0, 2, _data(0, 3));
  patches(5).SetData(0, 3, _data(0, 3));

  patches(5).SetData(1, 0, _data(0, 1));
  patches(5).SetData(1, 1, _data(0, 2));
  patches(5).SetData(1, 2, _data(0, 3));
  patches(5).SetData(1, 3, _data(0, 3));

  patches(5).SetData(2, 0, _data(1, 1));
  patches(5).SetData(2, 1, _data(1, 2));
  patches(5).SetData(2, 2, _data(1, 3));
  patches(5).SetData(2, 3, _data(1, 3));

  patches(5).SetData(3, 0, _data(2, 1));
  patches(5).SetData(3, 1, _data(2, 2));
  patches(5).SetData(3, 2, _data(2, 3));
  patches(5).SetData(3, 3, _data(2, 3));

  // DOWN-RIGHT

  patches(6).SetData(0, 0, _data(1, 1));
  patches(6).SetData(0, 1, _data(1, 2));
  patches(6).SetData(0, 2, _data(1, 3));
  patches(6).SetData(0, 3, _data(1, 3));

  patches(6).SetData(1, 0, _data(2, 1));
  patches(6).SetData(1, 1, _data(2, 2));
  patches(6).SetData(1, 2, _data(2, 3));
  patches(6).SetData(1, 3, _data(2, 3));

  patches(6).SetData(2, 0, _data(3, 1));
  patches(6).SetData(2, 1, _data(3, 2));
  patches(6).SetData(2, 2, _data(3, 3));
  patches(6).SetData(2, 3, _data(3, 3));

  patches(6).SetData(3, 0, _data(3, 1));
  patches(6).SetData(3, 1, _data(3, 2));
  patches(6).SetData(3, 2, _data(3, 3));
  patches(6).SetData(3, 3, _data(3, 3));

  // DOWN-LEFT

  patches(7).SetData(0, 0, _data(1, 0));
  patches(7).SetData(0, 1, _data(1, 0));
  patches(7).SetData(0, 2, _data(1, 1));
  patches(7).SetData(0, 3, _data(1, 2));

  patches(7).SetData(1, 0, _data(2, 0));
  patches(7).SetData(1, 1, _data(2, 0));
  patches(7).SetData(1, 2, _data(2, 1));
  patches(7).SetData(1, 3, _data(2, 2));

  patches(7).SetData(2, 0, _data(3, 0));
  patches(7).SetData(2, 1, _data(3, 0));
  patches(7).SetData(2, 2, _data(3, 1));
  patches(7).SetData(2, 3, _data(3, 2));

  patches(7).SetData(3, 0, _data(3, 0));
  patches(7).SetData(3, 1, _data(3, 0));
  patches(7).SetData(3, 2, _data(3, 1));
  patches(7).SetData(3, 3, _data(3, 2));

  // UP-LEFT

  patches(8).SetData(0, 0, _data(0, 0));
  patches(8).SetData(0, 1, _data(0, 0));
  patches(8).SetData(0, 2, _data(0, 1));
  patches(8).SetData(0, 3, _data(0, 2));

  patches(8).SetData(1, 0, _data(0, 0));
  patches(8).SetData(1, 1, _data(0, 0));
  patches(8).SetData(1, 2, _data(0, 1));
  patches(8).SetData(1, 3, _data(0, 2));

  patches(8).SetData(2, 0, _data(1, 0));
  patches(8).SetData(2, 1, _data(1, 0));
  patches(8).SetData(2, 2, _data(1, 1));
  patches(8).SetData(2, 3, _data(1, 2));

  patches(8).SetData(3, 0, _data(2, 0));
  patches(8).SetData(3, 1, _data(2, 0));
  patches(8).SetData(3, 2, _data(2, 1));
  patches(8).SetData(3, 3, _data(2, 2));
}

GLvoid
myPatchManager::generateImages()
{
  _imageOfPatches.ResizeColumns(_patchCount);

  for (GLuint i = 0; i < _patchCount; i++) {
    _imageOfPatches[i] = patches[i].GenerateImage(30, 30);
    _imageOfPatches[i]->UpdateVertexBufferObjects();
  }
}

GLvoid
myPatchManager::renderImages()
{

  glEnable(GL_LIGHTING);
  MatFBSilver.Apply();

  for (GLuint i = 0; i < _patchCount; i++) {

    if (_imageOfPatches[i]) {
      if (!_imageOfPatches[i]->Render())
        cout << "Error, can't render the" << i << ".th patch" << endl;
    } else {
      cout << " Error, no image of interpolation " << i << "th" << endl;
    }
  }
}

GLvoid
myPatchManager::getData(BicubicBSplinePatch& _patch)
{
  for (GLuint i = 0; i < 4; i++) {
    for (GLuint j = 0; j < 4; j++) {
      _patch.GetData(i, j, _data(i, j));
    }
  }
}
myPatchManager::~myPatchManager()
{
  for (GLuint i = 0; i < _patchCount; i++) {
    delete _imageOfPatches[i];
    _imageOfPatches[i] = nullptr;
  }
}
}
