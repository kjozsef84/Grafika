#include "../Core/LinearCombination3.h"


namespace cagd
{
    class bicubicSplineArc3: public LinearCombination3
    {
        public:
            bicubicSplineArc3 (GLenum data_usage_flag = GL_STATIC_DRAW);
            GLboolean BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble>& values) const;
            GLboolean CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives& d) const;

            GLdouble blendingFunction0(GLdouble t) const;
            GLdouble blendingFunction1(GLdouble t) const;
            GLdouble blendingFunction2(GLdouble t) const;
            GLdouble blendingFunction3(GLdouble t) const;

            GLdouble blendingFunction0_1(GLdouble t) const;
            GLdouble blendingFunction1_1(GLdouble t) const;
            GLdouble blendingFunction2_1(GLdouble t) const;
            GLdouble blendingFunction3_1(GLdouble t) const;

            GLdouble blendingFunction0_2(GLdouble t) const;
            GLdouble blendingFunction1_2(GLdouble t) const;
            GLdouble blendingFunction2_2(GLdouble t) const;
            GLdouble blendingFunction3_2(GLdouble t) const;

    };
}
