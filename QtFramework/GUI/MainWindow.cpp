#include "MainWindow.h"

namespace cagd {
MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{
  setupUi(this);

  /*

    the structure of the main window's central widget

   *---------------------------------------------------*
   |                 central widget                    |
   |                                                   |
   |  *---------------------------*-----------------*  |
   |  |     rendering context     |   scroll area   |  |
   |  |       OpenGL widget       | *-------------* |  |
   |  |                           | | side widget | |  |
   |  |                           | |             | |  |
   |  |                           | |             | |  |
   |  |                           | *-------------* |  |
   |  *---------------------------*-----------------*  |
   |                                                   |
   *---------------------------------------------------*

  */
  _side_widget = new SideWidget(this);

  _scroll_area = new QScrollArea(this);
  _scroll_area->setWidget(_side_widget);
  _scroll_area->setSizePolicy(_side_widget->sizePolicy());
  _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

  _gl_widget = new GLWidget(this);

  centralWidget()->setLayout(new QHBoxLayout());
  centralWidget()->layout()->addWidget(_gl_widget);
  centralWidget()->layout()->addWidget(_scroll_area);

  // creating a signal slot mechanism between the rendering context and the side
  // widget
  connect(_side_widget->type_box,
          SIGNAL(currentIndexChanged(int)),
          _side_widget,
          SLOT(set_page(int)));
  connect(_side_widget->type_box,
          SIGNAL(currentIndexChanged(int)),
          _gl_widget,
          SLOT(set_type_index(int)));
  connect(_side_widget->rotate_x_slider,
          SIGNAL(valueChanged(int)),
          _gl_widget,
          SLOT(set_angle_x(int)));
  connect(_side_widget->rotate_y_slider,
          SIGNAL(valueChanged(int)),
          _gl_widget,
          SLOT(set_angle_y(int)));
  connect(_side_widget->rotate_z_slider,
          SIGNAL(valueChanged(int)),
          _gl_widget,
          SLOT(set_angle_z(int)));

  connect(_side_widget->zoom_factor_spin_box,
          SIGNAL(valueChanged(double)),
          _gl_widget,
          SLOT(set_zoom_factor(double)));

  connect(_side_widget->trans_x_spin_box,
          SIGNAL(valueChanged(double)),
          _gl_widget,
          SLOT(set_trans_x(double)));
  connect(_side_widget->trans_y_spin_box,
          SIGNAL(valueChanged(double)),
          _gl_widget,
          SLOT(set_trans_y(double)));
  connect(_side_widget->trans_z_spin_box,
          SIGNAL(valueChanged(double)),
          _gl_widget,
          SLOT(set_trans_z(double)));
  connect(_side_widget->comboBox,
          SIGNAL(currentIndexChanged(int)),
          _gl_widget,
          SLOT(set_combo_index(int)));
  connect(_side_widget->comboBox_2,
          SIGNAL(currentIndexChanged(int)),
          _gl_widget,
          SLOT(set_combo_index(int)));
  connect(_side_widget->comboBox_3,
          SIGNAL(currentIndexChanged(int)),
          _gl_widget,
          SLOT(set_combo_index(int)));
  connect(_side_widget->pointSpinBox,
          SIGNAL(valueChanged(int)),
          _gl_widget,
          SLOT(setWhichPoint(int)));
  connect(_side_widget->curveSpinBox,
          SIGNAL(valueChanged(int)),
          _gl_widget,
          SLOT(setWhichCurve(int)));
  connect(_side_widget->xDoubleSpinBox,
          SIGNAL(valueChanged(double)),
          _gl_widget,
          SLOT(setX(double)));
  connect(_side_widget->yDoubleSpinBox,
          SIGNAL(valueChanged(double)),
          _gl_widget,
          SLOT(setY(double)));
  connect(_side_widget->zDoubleSpinBox,
          SIGNAL(valueChanged(double)),
          _gl_widget,
          SLOT(setZ(double)));
  connect(_side_widget->radioButtonOpeClosedCurve,
          SIGNAL(clicked(bool)),
          _gl_widget,
          SLOT(setIsOpen(bool)));

  connect(_side_widget->cbShader,
          SIGNAL(currentIndexChanged(int)),
          _gl_widget,
          SLOT(setShaderNumber(int)));

  connect(_gl_widget,
          SIGNAL(xPointChanged(double)),
          _side_widget->xDoubleSpinBox,
          SLOT(setValue(double)));

  connect(_gl_widget,
          SIGNAL(yPointChanged(double)),
          _side_widget->yDoubleSpinBox,
          SLOT(setValue(double)));

  connect(_gl_widget,
          SIGNAL(zPointChanged(double)),
          _side_widget->zDoubleSpinBox,
          SLOT(setValue(double)));

  // surface ----------------------------
  connect(_side_widget->UspinBox,
          SIGNAL(valueChanged(int)),
          _gl_widget,
          SLOT(setUIndex(int)));
  connect(_side_widget->VspinBox,
          SIGNAL(valueChanged(int)),
          _gl_widget,
          SLOT(setVIndex(int)));

  // -------------------      surface signal

  connect(_gl_widget,
          SIGNAL(patchYPointChanged(double)),
          _side_widget->patchYSpinBox,
          SLOT(setValue(double)));

  connect(_gl_widget,
          SIGNAL(patchXPointChanged(double)),
          _side_widget->patchXSpinBox,
          SLOT(setValue(double)));

  connect(_gl_widget,
          SIGNAL(patchZPointChanged(double)),
          _side_widget->patchZSpinBox,
          SLOT(setValue(double)));

  connect(_side_widget->patchYSpinBox,
          SIGNAL(valueChanged(double)),
          _gl_widget,
          SLOT(setPatchY(double)));
  connect(_side_widget->patchXSpinBox,
          SIGNAL(valueChanged(double)),
          _gl_widget,
          SLOT(setPatchX(double)));
  connect(_side_widget->patchZSpinBox,
          SIGNAL(valueChanged(double)),
          _gl_widget,
          SLOT(setPatchZ(double)));
}

//--------------------------------
// implementation of private slots
//--------------------------------
void
MainWindow::on_action_Quit_triggered()
{
  qApp->exit(0);
}
}
