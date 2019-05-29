#include "myPatchManager.h"

namespace cagd {

myPatchManager::myPatchManager(int row, int col)
{
  int n = row - 1, m = col - 1;
  rowCount = row + 3;
  columnCount = col + 3;
  // if utype, vtype
  // ha periodik akkor + 3 amelyik iranyba
  _net.ResizeRows(row);
  _net.ResizeColumns(col);
  patches.ResizeRows(rowCount);
  patches.ResizeColumns(columnCount);
  _imageOfPatches.ResizeRows(rowCount);
  _imageOfPatches.ResizeColumns(columnCount);

  for (GLint i = 0; i <= n; i++) {
    for (GLint j = 0; j <= m; j++) {
      DCoordinate3& cp = _net(i, j);
      cp[0] = i;
      cp[1] = j;
      cp[2] = -2.0 + 2.0 * (GLdouble)rand() / (GLdouble)RAND_MAX;
    }
  }
}

GLvoid
myPatchManager::generateImage()
{

  int n = rowCount - 4, m = columnCount - 4;
  // clamped
  for (GLuint i = 1; i <= n - 2; i++) {
    for (GLuint j = 1; j <= m - 2; j++) {
      for (GLint k = -1; k <= 2; k++) {
        for (GLint l = -1; l <= 2; l++) {
          patches(i + 1, j + 1)(k + 1, l + 1) = _net(i + k, j + l);
        }
      }
      _imageOfPatches(i + 1, j + 1) =
        patches(i + 1, j + 1).GenerateImage(30, 30);
      _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
    }
  }
  // felso resz
  for (GLint i = -1; i <= 0; i++) {
    for (GLint j = 1; j <= m - 2; j++) {
      for (GLint k = -1; k <= 2; k++) {
        for (GLint l = -1; l <= 2; l++) {
          patches(i + 1, j + 1)(k + 1, l + 1) = _net(max(i + k, 0), j + l);
        }
      }
      _imageOfPatches(i + 1, j + 1) =
        patches(i + 1, j + 1).GenerateImage(30, 30);
      _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
    }
  }
  // also resz:

  for (GLint i = n - 1; i <= n; i++) {
    for (GLint j = 1; j <= m - 2; j++) {
      for (GLint k = -1; k <= 2; k++) {
        for (GLint l = -1; l <= 2; l++) {
          patches(i + 1, j + 1)(k + 1, l + 1) = _net(min(i + k, n), j + l);
        }
      }
      _imageOfPatches(i + 1, j + 1) =
        patches(i + 1, j + 1).GenerateImage(30, 30);
      _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
    }
  }

  // jobb oldal

  for (GLint i = 1; i <= n - 2; i++) {
    for (GLint j = m - 1; j <= m; j++) {
      for (GLint k = -1; k <= 2; k++) {
        for (GLint l = -1; l <= 2; l++) {
          patches(i + 1, j + 1)(k + 1, l + 1) = _net(i + k, min(j + l, m));
        }
      }
      _imageOfPatches(i + 1, j + 1) =
        patches(i + 1, j + 1).GenerateImage(30, 30);
      _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
    }
  }

  // bal oldal

  for (GLint i = 1; i <= n - 2; i++) {
    for (GLint j = -1; j <= 0; j++) {
      for (GLint k = -1; k <= 2; k++) {
        for (GLint l = -1; l <= 2; l++) {
          patches(i + 1, j + 1)(k + 1, l + 1) = _net(i + k, max(j + l, 0));
        }
      }
      _imageOfPatches(i + 1, j + 1) =
        patches(i + 1, j + 1).GenerateImage(30, 30);
      _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
    }
  }

  // sarkok,

  for (GLint k = -1; k <= 2; k++) {
    for (GLint l = -1; l <= 2; l++) {
      patches(0, 0)(k + 1, l + 1) = _net(max(k, 0), max(l, 0));
    }
  }
  _imageOfPatches(0, 0) = patches(0, 0).GenerateImage(30, 30);
  _imageOfPatches(0, 0)->UpdateVertexBufferObjects();

  for (GLint k = -1; k <= 2; k++) {
    for (GLint l = -1; l <= 2; l++) {
      patches(n, m)(k + 1, l + 1) = _net(min(n + k - 1, n), min(m + l - 1, m));
    }
  }
  _imageOfPatches(n, m) = patches(n, m).GenerateImage(30, 30);
  _imageOfPatches(n, m)->UpdateVertexBufferObjects();

  // 2. atlo, de csak rajzon
  for (GLint k = -1; k <= 2; k++) {
    for (GLint l = -1; l <= 2; l++) {
      patches(0, m)(k + 1, l + 1) = _net(max(k, 0), min(m + l - 1, m));
    }
  }
  _imageOfPatches(0, m) = patches(0, m).GenerateImage(30, 30);
  _imageOfPatches(0, m)->UpdateVertexBufferObjects();

  for (GLint k = -1; k <= 2; k++) {
    for (GLint l = -1; l <= 2; l++) {
      patches(n, 0)(k + 1, l + 1) = _net(min(n + k - 1, n), max(l, 0));
    }
  }
  _imageOfPatches(n, 0) = patches(n, 0).GenerateImage(30, 30);
  _imageOfPatches(n, 0)->UpdateVertexBufferObjects();
  // clamped
  for (GLuint i = 1; i <= n - 2; i++) {
    for (GLuint j = 1; j <= m - 2; j++) {
      for (GLint k = -1; k <= 2; k++) {
        for (GLint l = -1; l <= 2; l++) {
          patches(i + 1, j + 1)(k + 1, l + 1) = _net(i + k, j + l);
        }
      }
      _imageOfPatches(i + 1, j + 1) =
        patches(i + 1, j + 1).GenerateImage(30, 30);
      _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
    }
  }
  // felso resz
  for (GLint i = -1; i <= 0; i++) {
    for (GLint j = 1; j <= m - 2; j++) {
      for (GLint k = -1; k <= 2; k++) {
        for (GLint l = -1; l <= 2; l++) {
          patches(i + 1, j + 1)(k + 1, l + 1) = _net(max(i + k, 0), j + l);
        }
      }
      _imageOfPatches(i + 1, j + 1) =
        patches(i + 1, j + 1).GenerateImage(30, 30);
      _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
    }
  }
  // also resz:

  for (GLint i = n - 1; i <= n; i++) {
    for (GLint j = 1; j <= m - 2; j++) {
      for (GLint k = -1; k <= 2; k++) {
        for (GLint l = -1; l <= 2; l++) {
          patches(i + 1, j + 1)(k + 1, l + 1) = _net(min(i + k, n), j + l);
        }
      }
      _imageOfPatches(i + 1, j + 1) =
        patches(i + 1, j + 1).GenerateImage(30, 30);
      _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
    }
  }

  // jobb oldal

  for (GLint i = 1; i <= n - 2; i++) {
    for (GLint j = m - 1; j <= m; j++) {
      for (GLint k = -1; k <= 2; k++) {
        for (GLint l = -1; l <= 2; l++) {
          patches(i + 1, j + 1)(k + 1, l + 1) = _net(i + k, min(j + l, m));
        }
      }
      _imageOfPatches(i + 1, j + 1) =
        patches(i + 1, j + 1).GenerateImage(30, 30);
      _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
    }
  }

  // bal oldal

  for (GLint i = 1; i <= n - 2; i++) {
    for (GLint j = -1; j <= 0; j++) {
      for (GLint k = -1; k <= 2; k++) {
        for (GLint l = -1; l <= 2; l++) {
          patches(i + 1, j + 1)(k + 1, l + 1) = _net(i + k, max(j + l, 0));
        }
      }
      _imageOfPatches(i + 1, j + 1) =
        patches(i + 1, j + 1).GenerateImage(30, 30);
      _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
    }
  }

  // sarkok,

  for (GLint k = -1; k <= 2; k++) {
    for (GLint l = -1; l <= 2; l++) {
      patches(0, 0)(k + 1, l + 1) = _net(max(k, 0), max(l, 0));
    }
  }
  _imageOfPatches(0, 0) = patches(0, 0).GenerateImage(30, 30);
  _imageOfPatches(0, 0)->UpdateVertexBufferObjects();

  for (GLint k = -1; k <= 2; k++) {
    for (GLint l = -1; l <= 2; l++) {
      patches(n, m)(k + 1, l + 1) = _net(min(n + k - 1, n), min(m + l - 1, m));
    }
  }
  _imageOfPatches(n, m) = patches(n, m).GenerateImage(30, 30);
  _imageOfPatches(n, m)->UpdateVertexBufferObjects();

  // 2. atlo, de csak rajzon
  for (GLint k = -1; k <= 2; k++) {
    for (GLint l = -1; l <= 2; l++) {
      patches(0, m)(k + 1, l + 1) = _net(max(k, 0), min(m + l - 1, m));
    }
  }
  _imageOfPatches(0, m) = patches(0, m).GenerateImage(30, 30);
  _imageOfPatches(0, m)->UpdateVertexBufferObjects();

  for (GLint k = -1; k <= 2; k++) {
    for (GLint l = -1; l <= 2; l++) {
      patches(n, 0)(k + 1, l + 1) = _net(min(n + k - 1, n), max(l, 0));
    }
  }
  _imageOfPatches(n, 0) = patches(n, 0).GenerateImage(30, 30);
  _imageOfPatches(n, 0)->UpdateVertexBufferObjects();
}

GLvoid
myPatchManager::renderControlPoints()
{
  glDisable(GL_LIGHTING);
  glPointSize(7);
  glColor3f(1, 0, 1);
  glBegin(GL_POINTS);
  for (GLuint i = 0; i < _net.GetRowCount(); i++) {
    for (GLuint j = 0; j < _net.GetColumnCount(); j++) {
      glVertex3f(_net(i, j).x(), _net(i, j).y(), _net(i, j).z());
    }
  }

  glEnd();

  glEnable(GL_LIGHTING);
}
GLvoid
myPatchManager::renderImages()
{

  glEnable(GL_LIGHTING);
  MatFBSilver.Apply();

  for (GLuint i = 0; i < rowCount; i++) {

    for (GLuint j = 0; j < columnCount; j++) {
      if (_imageOfPatches(i, j)) {
        // _imageOfPatches(i, j)->RenderNormals();
        if (!_imageOfPatches(i, j)->Render())
          cout << "Error, can't render the" << i << ".th patch" << endl;
      }
    }
  }
  glDisable(GL_LIGHTING);
}

DCoordinate3
myPatchManager::getPoint(int row, int col)
{
  return _net(row, col);
}
GLint
myPatchManager::getPointCountU()
{
  return rowCount - 4;
}
GLint
myPatchManager::getPointCountV()
{
  return columnCount - 4;
}

GLvoid
myPatchManager::changeControllPoint(int whichRow,
                                    int whichCol,
                                    DCoordinate3 point)
{

  cout << whichRow << " " << whichCol << endl;
  if (whichRow >= rowCount - 3 || whichCol >= columnCount) {
    return;
  }

  GLint n = rowCount - 4, m = columnCount - 4;
  _net(whichRow, whichCol) = point;

  if (whichRow >= 2 && whichRow <= n - 2 && whichCol >= 2 &&
      whichCol <= m - 2) {
    for (GLint i = whichRow - 2; i <= whichRow + 2; i++) {
      for (GLint j = whichCol - 2; j <= whichCol + 2; j++) {
        for (GLint k = -1; k <= 2; k++) {
          for (GLint l = -1; l <= 2; l++) {
            patches(i + 1, j + 1)(k + 1, l + 1) =
              _net(max(i + k, (int)0), max(j + l, (int)0));
          }
        }
        _imageOfPatches(i + 1, j + 1) =
          patches(i + 1, j + 1).GenerateImage(30, 30);
        _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
      }
    }
  } else if (whichRow < 2 && whichCol > 2 && whichCol <= m - 2) {

    // felso resz
    for (GLint i = -1; i <= 2; i++) {
      for (GLint j = whichCol - 2; j <= whichCol + 2; j++) {
        for (GLint k = -1; k <= 2; k++) {
          for (GLint l = -1; l <= 2; l++) {
            patches(i + 1, j + 1)(k + 1, l + 1) =
              _net(max(i + k, 0), min(j + l, m));
          }
        }
        _imageOfPatches(i + 1, j + 1) =
          patches(i + 1, j + 1).GenerateImage(30, 30);
        _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
      }
    }
    // also resz:
  } else if (whichRow > n - 2 && whichCol >= 2 && whichCol <= m - 2) {

    for (GLint i = n - 3; i <= n; i++) {
      for (GLint j = whichCol - 2; j <= whichCol + 2; j++) {
        for (GLint k = -1; k <= 2; k++) {
          for (GLint l = -1; l <= 2; l++) {
            patches(i + 1, j + 1)(k + 1, l + 1) =
              _net(min(i + k, n), min(max(j + l, 0), m));
          }
        }
        _imageOfPatches(i + 1, j + 1) =
          patches(i + 1, j + 1).GenerateImage(30, 30);
        _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
      }
    }
  } else if (whichRow > 2 && whichRow <= n - 2 && whichCol >= m - 2) {
    // jobb oldal

    for (GLint i = whichRow - 2; i <= whichRow + 2; i++) {
      for (GLint j = whichCol - 2; j <= m; j++) {
        for (GLint k = -1; k <= 2; k++) {
          for (GLint l = -1; l <= 2; l++) {
            patches(i + 1, j + 1)(k + 1, l + 1) =
              _net(min(i + k, n), min(j + l, m));
          }
        }

        _imageOfPatches(i + 1, j + 1) =
          patches(i + 1, j + 1).GenerateImage(30, 30);
        _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
      }
    }
  } else {
    // bal oldal

    for (GLint i = 1; i <= n - 2; i++) {
      for (GLint j = -1; j <= 0; j++) {
        for (GLint k = -1; k <= 2; k++) {
          for (GLint l = -1; l <= 2; l++) {
            patches(i + 1, j + 1)(k + 1, l + 1) = _net(i + k, max(j + l, 0));
          }
        }
        _imageOfPatches(i + 1, j + 1) =
          patches(i + 1, j + 1).GenerateImage(30, 30);
        _imageOfPatches(i + 1, j + 1)->UpdateVertexBufferObjects();
      }
    }

    // sarkok,

    for (GLint k = -1; k <= 2; k++) {
      for (GLint l = -1; l <= 2; l++) {
        patches(0, 0)(k + 1, l + 1) = _net(max(k, 0), max(l, 0));
      }
    }
    _imageOfPatches(0, 0) = patches(0, 0).GenerateImage(30, 30);
    _imageOfPatches(0, 0)->UpdateVertexBufferObjects();

    for (GLint k = -1; k <= 2; k++) {
      for (GLint l = -1; l <= 2; l++) {
        patches(n, m)(k + 1, l + 1) =
          _net(min(n + k - 1, n), min(m + l - 1, m));
      }
    }
    _imageOfPatches(n, m) = patches(n, m).GenerateImage(30, 30);
    _imageOfPatches(n, m)->UpdateVertexBufferObjects();

    // 2. atlo, de csak rajzon
    for (GLint k = -1; k <= 2; k++) {
      for (GLint l = -1; l <= 2; l++) {
        patches(0, m)(k + 1, l + 1) = _net(max(k, 0), min(m + l - 1, m));
      }
    }
    _imageOfPatches(0, m) = patches(0, m).GenerateImage(30, 30);
    _imageOfPatches(0, m)->UpdateVertexBufferObjects();

    for (GLint k = -1; k <= 2; k++) {
      for (GLint l = -1; l <= 2; l++) {
        patches(n, 0)(k + 1, l + 1) = _net(min(n + k - 1, n), max(l, 0));
      }
    }
    _imageOfPatches(n, 0) = patches(n, 0).GenerateImage(30, 30);
    _imageOfPatches(n, 0)->UpdateVertexBufferObjects();
  }
}

GLvoid
myPatchManager::setControlPoint(int i, int j, DCoordinate3 point)
{
  _net(i, j) = point;
}

}
