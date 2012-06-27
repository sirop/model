#include "ImportKml.h"

#include <QtCore/QTimer>
#include <QtCore/QFile>

#include "GeoDataCoordinates.h"
#include "GeoDataParser.h"
#include "GeoDocument.h"
#include "GeoDataDocument.h"
#include "GeoDataTypes.h"
#include "GeoDataData.h"
#include "GeoDataFolder.h"
#include "GeoDataPlacemark.h"
#include "GeoDataLineString.h"
#include "GeoDataLinearRing.h"
#include "GeoDataPolygon.h"
#include "MarbleDebug.h"

using namespace Marble;

QMap <QString,GeoDataLineString> ImportKml::CountryBoxes = QMap <QString,GeoDataLineString>();

ImportKml::ImportKml(QString  filename)
{
  KmlFile = filename;
}

void
ImportKml::importKmlFromData (QString  filename)
{
  GeoDataParser parser( GeoData_KML );
  QFile file(filename);
  if ( !file.exists() ) {
    qDebug() << filename <<" was not found";
    return;
  }

  // Open file in right mode
  if(!file.open( QIODevice::ReadOnly )){
    qDebug() << "Could not open kml file.";
    return;
  }
  if ( !parser.read( &file ) ) {
    qDebug() << "Could not import kml file.";
    return;
  }

  GeoDocument* doc = parser.releaseDocument();
  if ( doc ) {
    GeoDataDocument* document = dynamic_cast<GeoDataDocument*>( doc );
    if ( document && document->size() > 0 ) {
      document->setDocumentRole( UserDocument );
      document->setFileName(filename);
      qDebug()<< document->name();
      createCountryBoxes(document);
    }
  } else {
      qDebug()<< "Parsing failed";
  }

  file.close();
}

void
ImportKml::createCountryBoxes( GeoDataContainer *container )
{
  if ( !container ) {
    qDebug()<< "No GeoDataContainer";
    return;
  }

  QVector<GeoDataPlacemark*> PMVector = container->placemarkList();
  qDebug()<< "PMVector.size()=" << PMVector.size();
  for (int i = 0; i < PMVector.size(); ++i){
    GeoDataGeometry* geometry = PMVector.at(i)->geometry();
    GeoDataLineString* linestring = dynamic_cast<GeoDataLineString*>( geometry );
    qDebug()<<PMVector.at(i)->name();
    if(linestring){
    const GeoDataLineString* LineString = linestring;
    qDebug()<<PMVector.at(i)->name();
    qDebug()<< LineString->first().latitude(GeoDataCoordinates::Degree);
    const QString CountryName = PMVector.at(i)->name();
    CountryBoxes.insert( CountryName, *LineString);}
  }
}

QString
ImportKml::getKmlFile()
{
  //qDebug()<< KmlFile;
  return KmlFile;
}
