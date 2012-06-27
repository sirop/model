//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2012      Dennis Nienhüser <earthwings@gentoo.org>
//

#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtGui/QApplication>
#include <QtGui/QTreeView>

#include <marble/MarbleWidget.h>
#include <marble/MarbleModel.h>
#include <marble/MarbleRunnerManager.h>

#include <marble/GeoDataTreeModel.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/GeoDataMultiGeometry.h>

#include <ImportKml.h>
#include <MyMarbleWidget.h>

using namespace Marble;

int main(int argc, char** argv)
{
  QApplication app(argc,argv);
  ImportKml KmlData(app.arguments().last());
  KmlData.importKmlFromData(KmlData.getKmlFile());

  QFileInfo inputFile( app.arguments().last() );
  if ( app.arguments().size() < 2 || !inputFile.exists() ) {
    qWarning() << "Usage: " << app.arguments().first() << "file.kml";
    return 1;
  }

    MarbleModel model;
    MarbleRunnerManager manager( model.pluginManager() );

    GeoDataDocument* document = manager.openFile( inputFile.absoluteFilePath() );
    if ( !document ) {
        qDebug() << "Unable to open " << inputFile.absoluteFilePath();
        return 2;
    }

    GeoDataTreeModel treeModel;
    treeModel.addDocument( document );
   /* QString DocString = treeModel.data(treeModel.index(document), Qt::DisplayRole).toString ();
    qDebug() << DocString;
    //QString CountryString("Afganistan");
    //GeoDataPlacemark *pm = new GeoDataPlacemark("Afganistan");
    QModelIndex indexA = treeModel.index(0, 0, QModelIndex());
    QVariant v = treeModel.data( indexA, Qt::DisplayRole);
    qDebug()<< v ;
    QModelIndex indexB = treeModel.index(0, 0, indexA);
    v = treeModel.data(treeModel.index(0,1, indexB), Qt::DisplayRole);
    //QVariant v = treeModel.index(document).child(0,0).child(0,1).data();
    qDebug()<< v.typeName();*/
    /*GeoDataPolygon mg();
    if (v.canConvert<GeoDataPolygon>())
    mg = v.value<GeoDataPolygon>();*/
   /* qDebug()<< v ;
    QModelIndex indexC = treeModel.index(0, 0, indexB);
  v = treeModel.data( treeModel.index(0,1, indexC), Qt::DisplayRole);
  qDebug()<< v ;
  QModelIndex indexD = treeModel.index(0, 0, indexC);
  v = treeModel.data(treeModel.index(0,1, indexD), Qt::DisplayRole);*/
  /*qDebug()<< v.typeName();
  qDebug()<< v.toString() ;
  qDebug() << treeModel.columnCount();
  qDebug() << treeModel.rowCount();
  qDebug() << treeModel.headerData(2,Qt::Horizontal).toString();*/

  QTreeView treeView;
  treeView.setModel( &treeModel );
  treeView.show();

  MyMarbleWidget *mapWidget = new MyMarbleWidget;
  mapWidget->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
  mapWidget->show();
  GeoPainter *p=new GeoPainter(mapWidget,  mapWidget->viewport(), NormalQuality, false);
  mapWidget->customPaint(p);
  return app.exec();
}
