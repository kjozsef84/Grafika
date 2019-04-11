#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"

using namespace cagd;
using namespace std;

GLdouble spiral_on_cone::u_min = -TWO_PI;
GLdouble spiral_on_cone::u_max = +TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
}
//-----------------------------------       firstCurve      -----------------------------------------------------

GLdouble firstCurve::u_min = -PI;
GLdouble firstCurve::u_max = +PI;

DCoordinate3 firstCurve::d0(GLdouble u)
{
    return DCoordinate3(u,cos(2*u), sin(2*u));
}

DCoordinate3 firstCurve::d1(GLdouble u)
{
    return DCoordinate3(1.0, -2*sin(2 *u), 2*cos(2 *u));
}

DCoordinate3 firstCurve::d2(GLdouble u)
{
    return DCoordinate3(0, -4 * cos( 2 * u ), -4 * sin( 2 * u ) );
}

//-----------------------------------       secondCurve      -----------------------------------------------------

GLdouble secondCurve::u_min = -PI;
GLdouble secondCurve::u_max = PI;

DCoordinate3 secondCurve::d0(GLdouble u)
{
    return DCoordinate3(3 * cos(u), 3 * sin(u), 3 * cos(u) + 3 * sin(u) );
}

DCoordinate3 secondCurve::d1(GLdouble u)
{
    return DCoordinate3(-3 * sin(u),3 * cos(u), -3 * sin(u) + 3 * cos(u));
}

DCoordinate3 secondCurve::d2(GLdouble u)
{
    return DCoordinate3( -3 * cos(u), -3 * sin (u), -3 * cos(u) -3 * sin(u) );
}


//-----------------------------------       vivianCurve     -----------------------------------------------------

GLdouble vivianCurve::u_min = -TWO_PI;
GLdouble vivianCurve::u_max = TWO_PI;

DCoordinate3 vivianCurve::d0(GLdouble u)
{
    return DCoordinate3( 2 * (1 + cos(u) ), 2 * sin(u), 4 * sin(u/2));
}

DCoordinate3 vivianCurve::d1(GLdouble u)
{
    return DCoordinate3( -2 * sin(u), 2 * cos(u), 2 * cos(u/2));
}

DCoordinate3 vivianCurve::d2(GLdouble u)
{
    return DCoordinate3(-2* cos(u), -2 * sin(u), -1 * sin(u/2));
}


//-----------------------------------       thirdCurve     -----------------------------------------------------
//pdf 26, a = 2
GLdouble thirdCurve::u_min = -PI;
GLdouble thirdCurve::u_max = PI;

DCoordinate3 thirdCurve::d0(GLdouble u)
{
    return DCoordinate3(  2 *( cos(u) + u * sin (u) ), 2 *( sin(u) - u * cos(u)), u);
}

DCoordinate3 thirdCurve::d1(GLdouble u)
{
    return DCoordinate3( 2 * ( u * cos(u) ), 2*(u * sin(u) ), 1);
}

DCoordinate3 thirdCurve::d2(GLdouble u)
{
    return DCoordinate3( 2 * ( cos(u) - u * sin(u) ), 2 * ( sin (u) + u * cos(u)),0);
}

//-----------------------------------       roseCurve     -----------------------------------------------------

GLdouble roseCurve::u_min = -PI;
GLdouble roseCurve::u_max = PI;

DCoordinate3 roseCurve::d0(GLdouble u)
{
    return DCoordinate3((1/2 + cos(3 * u) ) * cos(u), (1/2 + cos(3 * u) ) * sin(u) );
}

DCoordinate3 roseCurve::d1(GLdouble u)
{
    return DCoordinate3( -3 * sin(3 * u) * cos(u) - sin(u) * ( 1/2 *cos(3 *u) ) , -3 * sin(3 * u) * sin(u) + cos(u) * (1/2 + cos(3 *u)));
}

DCoordinate3 roseCurve::d2(GLdouble u)
{
    return DCoordinate3( -3 * ( 3 * cos(3 * u) * cos(u) - sin(u) * sin(3 * u)) -1 * cos(u) * ( 1/2 + cos(3*u) ) + 3 * sin(u) * sin(u),
                         -3 *( 3 * cos(3 * u ) * sin(u) ) + sin(3 *u) * cos(u) -1 * sin(u) * (1/2 + cos(3 * u)) -3 * cos(u) * sin(3*u)  );
}



//------------------------------------------------      SURFACE     --------------------------------------------------------------------------

GLdouble firstSurface::u_min = 0;
GLdouble firstSurface::u_max = PI;
GLdouble firstSurface::v_min = 0;
GLdouble firstSurface::v_max = TWO_PI;

DCoordinate3 firstSurface::d00(GLdouble u, GLdouble v){

    return DCoordinate3( sin(u) * cos(v), sin(u) * sin(v), cos(u));
}

DCoordinate3 firstSurface::d10(GLdouble u, GLdouble v){

    return DCoordinate3( cos(v) * cos(u), cos(u) * sin(v), -1 * sin(u));
}


DCoordinate3 firstSurface::d01(GLdouble u,GLdouble v){

    return DCoordinate3( -1 *sin(v) * sin(u), sin(u) * cos(v), 0);
}


//-----------------------------

GLdouble secondSurface::u_min = -0;
GLdouble secondSurface::u_max = 3;
GLdouble secondSurface::v_min = 0;
GLdouble secondSurface::v_max = TWO_PI;

DCoordinate3 secondSurface::d00(GLdouble u, GLdouble v){

    return DCoordinate3( 2 * sin(v),2 * cos(v), u);
}

DCoordinate3 secondSurface::d10(GLdouble u,GLdouble v){

    return DCoordinate3( 0,0,1);
}

DCoordinate3 secondSurface::d01(GLdouble u, GLdouble v){

    return DCoordinate3(  2 * cos(v),-2 * sin(v), 0);
}

//--------------------------------------


GLdouble thirdSurface::u_min = -1;
GLdouble thirdSurface::u_max = 1;
GLdouble thirdSurface::v_min = -1;
GLdouble thirdSurface::v_max = 1;

DCoordinate3 thirdSurface::d00(GLdouble u, GLdouble v){

    return DCoordinate3(u, v, u*v);
}

DCoordinate3 thirdSurface::d10(GLdouble u,GLdouble v){

    return DCoordinate3( 1,0,v);
}

DCoordinate3 thirdSurface::d01(GLdouble u, GLdouble v){

    return DCoordinate3( 0, -2 * sin(v), 2 * cos(v));
}



//--------------------------------------


GLdouble forthSurface::u_min = -PI;
GLdouble forthSurface::u_max = PI;
GLdouble forthSurface::v_min = -PI;
GLdouble forthSurface::v_max = PI;

DCoordinate3 forthSurface::d00(GLdouble u, GLdouble v){

    return DCoordinate3( cos(u) * cos(v), u, cos(u) * sin(v) );
}

DCoordinate3 forthSurface::d10(GLdouble u,GLdouble v){

    return DCoordinate3(  cos(v) * -1 * sin(u), 1, - sin(u)*sin(v));
}

DCoordinate3 forthSurface::d01(GLdouble u, GLdouble v){

    return DCoordinate3(  cos(u) * -1 * sin(v), 0, cos(u) * cos(v));
}

//--------------------------------


GLdouble fifthSurface::u_min = 0;
GLdouble fifthSurface::u_max = PI;
GLdouble fifthSurface::v_min = 0;
GLdouble fifthSurface::v_max = PI;

DCoordinate3 fifthSurface::d00(GLdouble u, GLdouble v){

    return DCoordinate3( sin(2*u) * cos(v) * cos(v), sin(u) * sin(2*v)/2, cos(2*u) * cos(v) * cos(v));
}

DCoordinate3 fifthSurface::d10(GLdouble u,GLdouble v){

    return DCoordinate3(  cos(v) * cos(v) * 2 * cos(2 * u), sin(2*v)/2 * cos(u), cos(v) * cos (v) * -2 * sin(2 * u));
}

DCoordinate3 fifthSurface::d01(GLdouble u, GLdouble v){

    return DCoordinate3(  sin(2*u) * -2 * cos(v) * sin(v),sin(u)* cos(2 * v), cos(2 * u ) * -2 * cos(v) * sin(v));
}
