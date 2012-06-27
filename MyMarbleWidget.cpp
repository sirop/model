#include <QtCore>

#include "MyMarbleWidget.h"
#include "ImportKml.h"

#include <MarbleWidget.h>
#include <GeoPainter.h>
#include <GeoDataLineString.h>
#include <GeoDataLinearRing.h>
#include <GeoDataCoordinates.h>

void
MyMarbleWidget::importCountryMiddle(QString filename)
{
  QFile file(filename);
  if ( !file.exists() ) {
    qDebug() << filename <<" was not found";
    return;
  }
  // Open file in right mode
  if(!file.open( QIODevice::ReadOnly )){
    qDebug() << "Could not open country-coordinates.csv.";
    return;
  }
  QTextStream in(&file);
  while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList list = line.split(",", QString::SkipEmptyParts);
    GeoDataCoordinates gc(list[1].toDouble() , list[2].toDouble(),GeoDataCoordinates::Degree);
    CountryMiddle.insert(list[0],gc);
  }

}

void
MyMarbleWidget::customPaint(GeoPainter* painter)
{
  painter->setPen(Qt::green);
    //painter->drawEllipse(p1, 20, 20);
    //painter->setPen(Qt::black);
    //painter->drawLine (p1,p2 ,true );
    //GeoDataGeometry gdp(gdls);
    //GeoDataLinearRing gdlr(gdp);
    //painter->drawPolygon(gdls, Qt::OddEvenFill);
   //QMap <QString,GeoDataLineString> cp = KmlReader::countryPolygon;
  /*QMapIterator<QString, GeoDataLineString>::const_iterator i = ImportKml::CountryBoxes.constBegin();
  while (i != ImportKml::CountryBoxes.constEnd()) {
    painter->drawPolygon(i.value(), Qt::OddEvenFill);
    ++i;
  }*/
  QMap <QString,GeoDataLineString> Boxes = ImportKml::CountryBoxes;
  foreach (GeoDataLineString value, Boxes){
    painter->drawPolygon(value, Qt::OddEvenFill);
  }
  /*painter->setPen(Qt::blue);
  foreach (GeoDataLineString value, KmlReader::countryRectangle){
  painter->drawPolygon(value, Qt::OddEvenFill);
  GeoDataLatLonBox Box = GeoDataLatLonBox::fromLineString(value);
  //const QRectF Rect(  GeoDataCoordinates(Box.west(), Box.north(), Box.width(), Box.height() );
  qreal East = Box.east(GeoDataCoordinates::Degree);
  qreal West = Box.west(GeoDataCoordinates::Degree);
  qreal North = Box.north(GeoDataCoordinates::Degree);
  qreal South = Box.south(GeoDataCoordinates::Degree);
  const GeoDataCoordinates gc((East-West)/2+West, (North-South)/2+South, 0.0,GeoDataCoordinates::Degree);
  painter->drawRect(gc,Box.width(GeoDataCoordinates::Degree),Box.height(GeoDataCoordinates::Degree),true);
  GeoDataLinearRing LinearRing(value);
  if (LinearRing.contains(gc)){
      qDebug()<<gc.latitude(GeoDataCoordinates::Degree);
    }
  }
  */
}
