
#include "../Core/Matrices.h"
#include "../Core/DCoordinates3.h"
#include "../Core/GenericCurves3.h"
#include "mycycliccurve3.h"

namespace cagd
{
    class BicubicSplineManager {
        private:
            GLboolean isOpen;
            GLuint _n;
            GLuint _point_count;
            ColumnMatrix<DCoordinate3>  _points;
            bicubicSplineArc3 *bsArc3;
            GenericCurve3* _image_of_bsArc3;

        public:
            BicubicSplineManager(GLuint n, GLboolean isOpen = GL_FALSE);
            GLvoid FillMyGeometry();
            GLvoid UpdateMyGeometry();
            GLvoid RenderMyGeometry();
            GLvoid UpdateAndRender();
            GLvoid UpdateAndRenderOpen();
            GLvoid UpdateAndRenderClosed();
            GLvoid ChangeControllPoint(GLuint index, DCoordinate3 NewPoint);
            GLvoid ChangeControllPointOpen(GLuint index, DCoordinate3 NewPoint);
            GLvoid ChangeControllPointClosed(GLuint index, DCoordinate3 NewPoint);

    };
}
