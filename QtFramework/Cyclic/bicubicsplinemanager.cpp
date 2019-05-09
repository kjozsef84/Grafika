#include "bicubicsplinemanager.h"

#include <iostream>
using namespace std;

namespace cagd {

    BicubicSplineManager::BicubicSplineManager(GLuint n, GLboolean isOpen){
        this->isOpen = isOpen;
        _point_count = n + 16;
        _n = n;
    }

    GLvoid BicubicSplineManager::UpdateAndRender(){


        bsArc3 = new bicubicSplineArc3 ();

        if ( !isOpen ) {
            UpdateAndRenderOpen();
        } else {
            UpdateAndRenderClosed();
        }
    }

    GLvoid BicubicSplineManager::FillMyGeometry() {

        GLdouble step = 10;
        _points.ResizeRows(_point_count);

        for(GLuint i = 0; i < _n; i++)
        {
            GLdouble u = ( i ) * step;
            DCoordinate3 &cp = _points[i];
            cp[0] = cos(u);
            cp[1] = sin(u);
            cp[2] = -2.0 + 4.0 * (GLdouble)rand() / (GLdouble)RAND_MAX;
         }
    }


    GLvoid BicubicSplineManager::ChangeControllPoint(GLuint index, DCoordinate3 NewPoint) {
        if ( isOpen )
            ChangeControllPointOpen(index,NewPoint);
        else {
            ChangeControllPointClosed(index, NewPoint);
        }
    }


    GLvoid BicubicSplineManager::ChangeControllPointOpen(GLuint index, DCoordinate3 NewPoint) {
        _points[index] = NewPoint;
        if( !index ) {
            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = NewPoint;
            (*bsArc3)[2] = NewPoint;
            (*bsArc3)[3] = _points[1];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = NewPoint;
            (*bsArc3)[2] = _points[1];
            (*bsArc3)[3] = _points[2];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = _points[1];
            (*bsArc3)[2] = _points[2];
            (*bsArc3)[3] = _points[3];
            UpdateMyGeometry();
            RenderMyGeometry();

        } else if ( index == 1 ){

            (*bsArc3)[0] = _points[0];
            (*bsArc3)[1] = _points[0];
            (*bsArc3)[2] = _points[0];
            (*bsArc3)[3] = NewPoint;
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[0];
            (*bsArc3)[1] = _points[0];
            (*bsArc3)[2] = NewPoint;
            (*bsArc3)[3] = _points[2];
            UpdateMyGeometry();
            RenderMyGeometry();


            (*bsArc3)[0] = _points[0];
            (*bsArc3)[1] = NewPoint;
            (*bsArc3)[2] = _points[2];
            (*bsArc3)[3] = _points[3];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = _points[2];
            (*bsArc3)[2] = _points[3];
            (*bsArc3)[3] = _points[4];
            UpdateMyGeometry();
            RenderMyGeometry();
        } else if ( index == _n-1 ) {


            (*bsArc3)[0] = _points[_n-4];
            (*bsArc3)[1] = _points[_n-3];
            (*bsArc3)[2] = _points[_n-2];
            (*bsArc3)[3] = NewPoint;
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[_n-3];
            (*bsArc3)[1] = _points[_n-2];
            (*bsArc3)[2] = NewPoint;
            (*bsArc3)[3] = NewPoint;
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[_n-2];
            (*bsArc3)[1] = NewPoint;
            (*bsArc3)[2] = NewPoint;
            (*bsArc3)[3] = NewPoint;
            UpdateMyGeometry();
            RenderMyGeometry();

        } else if ( index = _n-2 ) {

            (*bsArc3)[0] = _points[_n-5];
            (*bsArc3)[1] = _points[_n-4];
            (*bsArc3)[2] = _points[_n-3];
            (*bsArc3)[3] = NewPoint;
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[_n-4];
            (*bsArc3)[1] = _points[_n-3];
            (*bsArc3)[2] = NewPoint;
            (*bsArc3)[3] = _points[_n-1];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[_n-3];
            (*bsArc3)[1] = NewPoint;
            (*bsArc3)[2] = _points[_n-1];
            (*bsArc3)[3] = _points[_n-1];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = _points[_n-1];
            (*bsArc3)[2] = _points[_n-1];
            (*bsArc3)[3] = _points[_n-1];
            UpdateMyGeometry();
            RenderMyGeometry();

        } else {

            GLuint n_1 = _n-1;
            (*bsArc3)[0] = _points[index-3];
            (*bsArc3)[1] = _points[index-2];
            (*bsArc3)[2] = _points[index-1];
            (*bsArc3)[3] = NewPoint;
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[index-2];
            (*bsArc3)[1] = _points[index-1];
            (*bsArc3)[2] = NewPoint;
            (*bsArc3)[3] = _points[(index+1) % n_1];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[index-1];
            (*bsArc3)[1] = NewPoint;
            (*bsArc3)[2] = _points[(index+1) % n_1];
            (*bsArc3)[3] = _points[(index+2) % n_1];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = _points[(index+1) % n_1];
            (*bsArc3)[2] = _points[(index+2) % n_1];
            (*bsArc3)[3] = _points[(index+3) % n_1];
            UpdateMyGeometry();
            RenderMyGeometry();

        }

    }
    GLvoid BicubicSplineManager::ChangeControllPointClosed(GLuint index, DCoordinate3 NewPoint){
        _points[index] = NewPoint;
        GLuint n_1 = _n - 1;
        if( !index ) {

            (*bsArc3)[0] = _points[n_1-2];
            (*bsArc3)[1] = _points[n_1-1];
            (*bsArc3)[2] = _points[n_1];
            (*bsArc3)[3] = NewPoint;
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[n_1-1];
            (*bsArc3)[1] = _points[n_1];
            (*bsArc3)[2] = NewPoint;
            (*bsArc3)[3] = _points[1];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[n_1-1];
            (*bsArc3)[1] = NewPoint;
            (*bsArc3)[2] = _points[1];
            (*bsArc3)[3] = _points[2];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = _points[1];
            (*bsArc3)[2] = _points[2];
            (*bsArc3)[3] = _points[3];
            UpdateMyGeometry();
            RenderMyGeometry();

        } else if ( index == 1 ){

            (*bsArc3)[0] = _points[4];
            (*bsArc3)[1] = _points[3];
            (*bsArc3)[2] = _points[2];
            (*bsArc3)[3] = NewPoint;
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[3];
            (*bsArc3)[1] = _points[2];
            (*bsArc3)[2] = NewPoint;
            (*bsArc3)[3] = _points[0];
            UpdateMyGeometry();
            RenderMyGeometry();


            (*bsArc3)[0] = _points[2];
            (*bsArc3)[1] = NewPoint;
            (*bsArc3)[2] = _points[0];
            (*bsArc3)[3] = _points[n_1];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = _points[0];
            (*bsArc3)[2] = _points[n_1];
            (*bsArc3)[3] = _points[n_1-1];
            UpdateMyGeometry();
            RenderMyGeometry();
        } else if ( index == 2 ) {

            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = _points[1];
            (*bsArc3)[2] = _points[0];
            (*bsArc3)[3] = _points[n_1];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[3];
            (*bsArc3)[1] = NewPoint;
            (*bsArc3)[2] = _points[1];
            (*bsArc3)[3] = _points[0];
            UpdateMyGeometry();
            RenderMyGeometry();


            (*bsArc3)[0] = _points[3];
            (*bsArc3)[1] = _points[2];
            (*bsArc3)[2] = NewPoint;
            (*bsArc3)[3] = _points[0];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = _points[3];
            (*bsArc3)[2] = _points[4];
            (*bsArc3)[3] = _points[5];
            UpdateMyGeometry();
            RenderMyGeometry();

        } else {
            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = _points[( index + 1 ) % _n];
            (*bsArc3)[2] = _points[( index + 2 ) % _n];
            (*bsArc3)[3] = _points[( index + 3) % _n];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = _points[( index - 1 ) % _n];
            (*bsArc3)[1] = NewPoint;
            (*bsArc3)[2] = _points[( index + 1 ) % _n];
            (*bsArc3)[3] = _points[( index + 2 ) % _n];
            UpdateMyGeometry();
            RenderMyGeometry();


            (*bsArc3)[0] = _points[( index - 2 ) % _n];
            (*bsArc3)[1] = _points[( index - 1 ) % _n];
            (*bsArc3)[2] = NewPoint;
            (*bsArc3)[3] = _points[( index + 1 ) % _n];
            UpdateMyGeometry();
            RenderMyGeometry();

            (*bsArc3)[0] = NewPoint;
            (*bsArc3)[1] = _points[( index + 1 ) % _n];
            (*bsArc3)[2] = _points[( index + 2 ) % _n];
            (*bsArc3)[3] = _points[( index + 3 ) % _n];
            UpdateMyGeometry();
            RenderMyGeometry();
        }

    }

    GLvoid BicubicSplineManager::UpdateAndRenderClosed(){

        GLuint aux = _n - 1;
        for( GLuint i = 0; i <= _n - 2; i++ ){

            (*bsArc3)[0] = _points[ (i % aux) ];
            (*bsArc3)[1] = _points[ ( ( i + 1 ) % aux) ];
            (*bsArc3)[2] = _points[ ( ( i + 2 ) % aux) ];
            (*bsArc3)[3] = _points[ ( ( i + 3 ) % aux) ];
            UpdateMyGeometry();
            RenderMyGeometry();
        }
    }

    GLvoid BicubicSplineManager::UpdateAndRenderOpen() {

        (*bsArc3)[0] = _points[0];
        (*bsArc3)[1] = _points[0];
        (*bsArc3)[2] = _points[0];
        (*bsArc3)[3] = _points[1];
        UpdateMyGeometry();
        RenderMyGeometry();

        (*bsArc3)[0] = _points[0];
        (*bsArc3)[1] = _points[0];
        (*bsArc3)[2] = _points[1];
        (*bsArc3)[3] = _points[2];
        UpdateMyGeometry();
        RenderMyGeometry();
// --------     orriginal points


        for( GLuint i = 4; i <= _n; i++ ){

            (*bsArc3)[0] = _points[i-4];
            (*bsArc3)[1] = _points[i-3];
            (*bsArc3)[2] = _points[i-2];
            (*bsArc3)[3] = _points[i-1];
            UpdateMyGeometry();
            RenderMyGeometry();

        }

//  ------ END  --------------------

        (*bsArc3)[0] = _points[_n-3];
        (*bsArc3)[1] = _points[_n-2];
        (*bsArc3)[2] = _points[_n-1];
        (*bsArc3)[3] = _points[_n-1];
        UpdateMyGeometry();
        RenderMyGeometry();

        (*bsArc3)[0] = _points[_n-2];
        (*bsArc3)[1] = _points[_n-1];
        (*bsArc3)[2] = _points[_n-1];
        (*bsArc3)[3] = _points[_n-1];
        UpdateMyGeometry();
        RenderMyGeometry();


    }

    GLvoid BicubicSplineManager::UpdateMyGeometry() {
        bsArc3->UpdateVertexBufferObjectsOfData();
        _image_of_bsArc3 = bsArc3->GenerateImage(2,400);

        if ( ! _image_of_bsArc3 ){
            throw ("Cannot create the image of my generic curve");
        }
        if ( !_image_of_bsArc3 ->UpdateVertexBufferObjects()) {
            cout << " Error, mycyclic curve, cannot update VBO s" << endl;
        }

    }

    GLvoid BicubicSplineManager::RenderMyGeometry() {
        glDisable(GL_LIGHTING);

        glPointSize(10.0f);
        glColor3f(1.0f,0.0f,0.0f);
           bsArc3->RenderData(GL_POINTS);
            if ( !_image_of_bsArc3->RenderDerivatives(0,GL_LINE_STRIP) ) {
                cout << " Error, the cyclic curve can't be render " << endl;
            }
         glPointSize(1.0f);
/*
        glColor3f(0.0f,0.8f,1.0f);
        _image_of_bsArc3->RenderDerivatives(1,GL_LINES);
        glColor3f(1.0f,0.8f,1.0f);
        _image_of_bsArc3->RenderDerivatives(2,GL_LINES);
        glPointSize(3.0f);
*/
    }
}
