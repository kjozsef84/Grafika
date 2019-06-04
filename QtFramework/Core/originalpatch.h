#include "mypatchmanager.h"

namespace cagd {

class originalPatch : public myPatchManager
{
public:
  originalPatch(int, int);
  GLvoid setContolPoints(int);
};

}
