#pragma once

#include "../Core/DCoordinates3.h"

namespace cagd {
namespace spiral_on_cone {
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

namespace firstCurve {
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

namespace secondCurve {
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

namespace vivianCurve {
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

namespace thirdCurve {
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

namespace roseCurve {
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

//-------------------------------------------------------------------------------------------------------

namespace firstSurface {
extern GLdouble u_min, u_max, v_min, v_max;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);

}

namespace secondSurface {
extern GLdouble u_min, u_max, v_min, v_max;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);

}

namespace thirdSurface {
extern GLdouble u_min, u_max, v_min, v_max;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);

}

namespace forthSurface {
extern GLdouble u_min, u_max, v_min, v_max;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);

}

namespace fifthSurface {
extern GLdouble u_min, u_max, v_min, v_max;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);

}

}
