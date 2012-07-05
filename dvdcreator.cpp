#include <QFile>
#include <QTextStream>
#include "dvdcreator.h"

DVDCreator::DVDCreator(QObject *parent) :
    QObject(parent)
{
    watchfolder = "C:/Dokumente und Einstellungen/andreas/Desktop/rocketDVDFiles/watchfolder";
    avsPath = "C:\\Dokumente und Einstellungen\\andreas\\Desktop\\rocketDVDFiles\\direct.avs";
    baseProjectPath = "C:/Dokumente und Einstellungen/andreas/Desktop/rocketDVDFiles/test.prj";
    menuTheme = "C:/Dokumente und Einstellungen/andreas/Desktop/rocketDVDFiles/mwa.menu";

}


void DVDCreator::createJobFile(){
    QFile file(watchfolder+"/out.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<"JobTemplate = "<<baseProjectPath<<"\n";
    out<<"JobID = QTTest\n";
    out<<"StartingStage = Transcode\n";
    out<<"Title = MWA is Sailing\n";
    out<<"Subtitle = Schwupps\n";
    out<<"Date = 1.1.13\n";
    out<<"Variable = [[Company Name]], Rumpelkammer\n";
    out<<"Variable = mytext, Eels\n";
    out<<"MenuTheme="<<menuTheme<<"\n";
    out<<"UsePre-EncodedFiles=yes\n";
    out<<"Pre-EncodedFileType = FilesToEncode\n";
    out<<"Pre-CapturedFile=VIDEO:"<<avsPath<<",LENGTH:0:20\n";

    file.close();
}

void DVDCreator::createAviSynthFile(){

}
