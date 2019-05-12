#pragma once

#include <GL/glew.h>
#include <QGLWidget>
#include <QGLFormat>
#include <QTimer>
#include "../Parametric/ParametricCurves3.h"
#include "../Core/TriangulatedMeshes3.h"
#include "../Core/DCoordinates3.h"
#include "../Core/Constants.h"
#include "../Core/GenericCurves3.h"
#include "Test/TestFunctions.h"
#include "../Core/Materials.h"
#include <Core/Exceptions.h>
#include "../Parametric/ParametricSurfaces3.h"
#include "../Cyclic/CyclicCurve3.h"
#include "../Core/bicubicbsplinepatch.h"
#include "../Cyclic/mycycliccurve3.h"
#include "../Cyclic/bicubicsplinemanager.h"
#include "../Core/ShaderPrograms.h"

namespace cagd
{
    class GLWidget: public QGLWidget
    {
        Q_OBJECT

    private:

        // variables defining the projection matrix
        float       _aspect;            // aspect ratio of the rendering window
        float       _fovy;              // field of view in direction y
        float       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix
        float       _eye[3], _center[3], _up[3];

        // variables needed by transformations
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        // your other declarations
/*
        ParametricCurve3 * _pc;
        GenericCurve3 * _imageOfPc;
*/
// ------------     Lab1    --------------

        GLuint _ps_selected;
        GLuint _pc_count;
        GLuint _pointCount;
        GLuint homeworkNumber = 1;
        RowMatrix<ParametricCurve3 *> _pc;
        RowMatrix<GenericCurve3 *> _img_pc;
        RowMatrix<GLdouble> _scale;

//------------      Lab2    ----------------

        QTimer *_timer;
        GLfloat _angle = 0;
        GLuint _mangle;

        TriangulatedMesh3 _animal;
        ShaderProgram _shader;

        GLuint _ps_count;
        RowMatrix<ParametricSurface3 *> _ps;
        RowMatrix<TriangulatedMesh3 *> _img_ps;


//------------      Lab4        ---------------

    CyclicCurve3* _cyc3;
    GenericCurve3* _image_of_cyc3;
    BicubicSplineManager * manager;
    GLuint _curve_number = 1;
    GLuint _point_number = 1;
    DCoordinate3 _points;
    GLboolean _open = GL_FALSE;


//------------      Lab4_2      ---------------

    BicubicBSplinePatch _patch;
    TriangulatedMesh3 *_before_interpolation, *_after_interpolation;

//------------      Private Slots

    private slots:
        void _animate();

    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);
        virtual ~GLWidget();

    public slots:
        // public event handling methods/slots
        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);

        void setParametricCurve( int index);
        void signalManagement();
        void setWhichCurve(int index);
        void setWhichPoint(int index);
        void setX(double);
        void setY(double);
        void setZ(double);
        void setIsOpen(bool);

    private slots:
        void _rotateModel();

    private:
        void initializeFirst();
        void drawFirst();
        void initializeAnimal();
        void drawAnimal();
        void initalizeSurface();
        void drawSurface();
        void initializeCyclicCurve();
        void renderCyclicCurve();
        void initializeBicubicSpline();
        void renderBicubicSpline();
        void initializeBicubicSplineArc3();
        void renderBicubicSplineArc3();
    };
}
