#pragma once

#include "../Core/Constants.h"
#include "../Core/DCoordinates3.h"
#include "../Core/GenericCurves3.h"
#include "../Core/Materials.h"
#include "../Core/ShaderPrograms.h"
#include "../Core/TriangulatedMeshes3.h"
#include "../Core/originalpatch.h"
#include "../Cyclic/CyclicCurve3.h"
#include "../Cyclic/bicubicsplinemanager.h"
#include "../Cyclic/mycycliccurve3.h"
#include "../Parametric/ParametricCurves3.h"
#include "../Parametric/ParametricSurfaces3.h"
#include "Test/TestFunctions.h"
#include <Core/Exceptions.h>
#include <GL/glew.h>
#include <QGLFormat>
#include <QGLWidget>
#include <QTimer>

namespace cagd {
class GLWidget : public QGLWidget
{
  Q_OBJECT

private:
  // variables defining the projection matrix
  float _aspect;         // aspect ratio of the rendering window
  float _fovy;           // field of view in direction y
  float _z_near, _z_far; // distance of near and far clipping planes

  // variables defining the model-view matrix
  float _eye[3], _center[3], _up[3];

  // variables needed by transformations
  int _angle_x, _angle_y, _angle_z;
  double _zoom;
  double _trans_x, _trans_y, _trans_z;

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
  int _type_index;
  int _combo_index;
  ParametricCurve3* _pc;
  RowMatrix<GenericCurve3*> _img_pc;
  GenericCurve3* _image_of_pc;
  RowMatrix<GLdouble> _scale;

  //------------      Lab2    ----------------

  QTimer* _timer;
  GLdouble _angle = 0;
  GLuint _mangle;

  TriangulatedMesh3 _elephant_model;
  TriangulatedMesh3 _mouse_model;
  TriangulatedMesh3 _sphere_model;
  ShaderProgram _shader;

  RowMatrix<ShaderProgram> _shaders;
  GLuint _selectedShader = 0;

  GLuint _ps_count;
  ParametricSurface3* _ps;
  TriangulatedMesh3* _image_of_ps;
  RowMatrix<TriangulatedMesh3*> _img_ps;
  RowMatrix<TriangulatedMesh3*> _image_of_ps_pointers;
  //------------      Lab4        ---------------

  CyclicCurve3* _cyc3 = nullptr;
  GenericCurve3* _image_of_cyc3;
  GenericCurve3* _image_of_cyc3_after;
  BicubicSplineManager* manager;
  GLuint _curve_number = 1;
  GLuint _point_number = 1;
  GLuint _oldPointNumber = 1;
  DCoordinate3 _points;
  GLboolean _open = GL_FALSE;

  //------------      Lab4_2      ---------------

  BicubicBSplinePatch _patch;
  TriangulatedMesh3* _before_interpolation = nullptr;
  TriangulatedMesh3* _after_interpolation;
  GLuint _ulineCount = 10;
  GLuint _vlineCount = 10;
  RowMatrix<GenericCurve3*>* uLines;
  RowMatrix<GenericCurve3*>* vLines;

  // ------------- shader uniform variables -------------------

  GLfloat scale_factor_parameter;
  GLfloat smoothing_parameter;
  GLfloat shading_parameter;

  // -------------  Patches

  myPatchManager* _patchManager = nullptr;
  GLint uIndex = 0, vIndex = 0;
  DCoordinate3 patchPoint;

  // ------------   Original patch

  originalPatch* myOriginalPatch = nullptr;
  GLuint myPatchIndex = 0;
  //------------      Private Slots

private slots:
  // void _animate();

public:
  // special and default constructor
  // the format specifies the properties of the rendering window
  GLWidget(QWidget* parent = nullptr,
           const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer |
                                     QGL::DoubleBuffer);

  // redeclared virtual functions
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  virtual ~GLWidget();
  void switch_parametric_curve(GLuint index);
  void init_models();
  void switch_parametric_surface(int index);
public slots:
  // public event handling methods/slots
  void set_angle_x(int value);
  void set_angle_y(int value);
  void set_angle_z(int value);

  void set_zoom_factor(double value);

  void set_trans_x(double value);
  void set_trans_y(double value);
  void set_trans_z(double value);

  // void setParametricCurve(int index);
  void set_type_index(int index);
  void set_combo_index(int index);
  void set_displayed_image();
  void signalManagement();
  void setWhichCurve(int index);
  void setWhichPoint(int index);
  void setX(double);
  void setY(double);
  void setZ(double);
  void setIsOpen(bool);
  void setShaderNumber(int);
  void setUIndex(int);
  void setVIndex(int);
  void changePatchPoint();
  void setPatchX(double);
  void setPatchY(double);
  void setPatchZ(double);

  void show_model();
  void show_parametric_surface();
  void show_parametric_curve();

  //------------- set uniform variables -------------------

  void setScaleFactor(double);
  void setSmoothing(double);
  void setShading(double);

  //  my patch

  void setPatchIndex(int);

signals:
  void xPointChanged(double);
  void yPointChanged(double);
  void zPointChanged(double);
  void patchXPointChanged(double);
  void patchYPointChanged(double);
  void patchZPointChanged(double);

private slots:
  // void _rotateModel();

private:
  void initialize_parametric_curve(GLuint index);
  // void drawFirst();
  void initializeModel();
  void drawModel();
  void drawSurface();
  void initializeCyclicCurve();
  void renderCyclicCurve();
  void initializeBicubicSpline();
  void renderBicubicSpline();
  void initializeBicubicSplineArc3();
  void renderBicubicSplineArc3();
  GLvoid initializePatchManager();
  GLvoid renderPatchManager();
  GLvoid setPatchData();
  GLvoid initializeControlNet();
  GLvoid renderControlNet();
  GLvoid initShader();
  GLvoid setPoints();
  GLvoid paintPoint(DCoordinate3);

  GLvoid initializeMyPatch();
  GLvoid renderMyPatch();
  void initialize_parametric_surface(int index);
};
}
