#ifndef IMPORTKML_H
#define IMPORTKML_H

#include <marble/GeoDataLineString.h>
#include <marble/GeoDataContainer.h>

using namespace Marble;

class ImportKml
{
  QString KmlFile;
public:
  ImportKml(QString filename);
  static QMap <QString,GeoDataLineString> CountryBoxes;
  void importKmlFromData(QString  filename);
  QString  getKmlFile();


private:
  //QString kmlfile;
  void createCountryBoxes( GeoDataContainer *container );
};






#endif
