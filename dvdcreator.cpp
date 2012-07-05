#include <QFile>
#include <QTextStream>
#include <QFileSystemWatcher>
#include <QDateTime>
#include <QDebug>
#include <QStringList>
#include "dvdcreator.h"

DVDCreator::DVDCreator(QObject *parent) :
    QObject(parent)
{
    watchfolder = "D:/RocketDVD/watchfolder/";
    avsPath = "D:\\RocketDVD\\direct.avs";
    baseProjectPath = "D:/RocketDVD/test.prj";
    menuTheme = "C:/Programme/Digital Media Applications/RocketDVD Professional Trial/Menu/CORPORATE - insert your own titles_PAL_MWA.menu";

   QFileSystemWatcher* watchFolderWatcher = new QFileSystemWatcher(this);
    watchFolderWatcher->addPath(watchfolder);

    connect(watchFolderWatcher,SIGNAL(fileChanged(QString)),this,SLOT(handleFileChanges(QString)));
    connect(watchFolderWatcher,SIGNAL(directoryChanged(QString)),this,SLOT(handleFileChanges(QString)));
    QString s;
    foreach (s, watchFolderWatcher->directories()){
        qDebug(s.toAscii());
    }
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
    out<<"Date = "<<QDateTime::currentDateTime().toString()<<"\n";
    out<<"Variable = [[Company Name]], Rumpelkammer\n";
    out<<"Variable = mytext, Eels\n";
    out<<"MenuTheme="<<menuTheme<<"\n";
    out<<"UsePre-EncodedFiles=yes\n";
    out<<"Pre-EncodedFileType = FilesToEncode\n";
    out<<"Pre-CapturedFile=VIDEO:"<<avsPath<<",LENGTH:0:20\n";

    file.close();
}

void DVDCreator::createAviSynthFile(bool resize = true, bool changeFps = true){
    QFile file(avsPath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<"DirectShowSource(\"Untitled 05.avi\")\n";
    if (changeFps){
        out<<"AssumeFPS(25)\n";
    }
    if (resize){
        out<<"LanczosResize(720, 576)\n";
    }
    file.close();
}

void DVDCreator::handleFileChanges(QString path){
    qDebug("HAAAAAA");
    qDebug(path.toAscii());
}

void DVDCreator::startDVDJob(){
    createAviSynthFile();
    createJobFile();
}
