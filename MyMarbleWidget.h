#ifndef MYMARBLEWIDGET_H
#define MYMARBLEWIDGET_H

#include <MarbleWidget.h>
#include <GeoPainter.h>
#include <GeoDataCoordiantes.h>

using namespace Marble;

class MyMarbleWidget : public MarbleWidget
{
public:
  QMap <QString,GeoDataCoordinates> CountryMiddle;
  void importCountryMiddle(QString filename);
  virtual void customPaint(GeoPainter* painter);
  friend class ImportKml;
};

#endif
