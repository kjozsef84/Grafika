#pragma once

#include "ui_SideWidget.h"
#include <QWidget>

namespace cagd {
class SideWidget
  : public QWidget
  , public Ui::SideWidget
{
  Q_OBJECT
public:
  // special and default constructor
  explicit SideWidget(QWidget* parent = nullptr);
public slots:
  void set_page(int index);
};
}
