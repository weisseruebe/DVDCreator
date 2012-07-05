#include <QFile>
#include <QTextStream>
#include <QFileSystemWatcher>
#include <QDateTime>
#include <QDebug>
#include <QStringList>
#include <QFile>
#include "dvdcreator.h"

DVDCreator::DVDCreator(QObject *parent) :
    QObject(parent)
{
    watchfolder = "D:/RocketDVD/watchfolder/";
    avsPath = "D:\\RocketDVD\\direct.avs";
    baseProjectPath = "D:/RocketDVD/test.prj";
    menuTheme = "C:/Programme/Digital Media Applications/RocketDVD Professional Trial/Menu/CORPORATE - insert your own titles_PAL_MWA.menu";

    watchFolderWatcher = new QFileSystemWatcher(this);
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

void DVDCreator::createAviSynthFile(QString videofile, bool resize = true, bool changeFps = true){
    QFile file(avsPath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<"DirectShowSource(\""<<videofile<<"\")\n";
    if (changeFps){
        out<<"AssumeFPS(25)\n";
    }
    if (resize){
        out<<"LanczosResize(720, 576)\n";
    }
    file.close();
}

void DVDCreator::handleFileChanges(QString path){
    qDebug(path.toAscii());
    if (QFile(watchfolder+"out.running").exists()){
        qDebug("Running");
        emit running("out");
    }
    if (QFile(watchfolder+"out.err").exists()){
        qDebug("Error");
        QFile file(watchfolder+"out.err");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            QString line = in.readLine();
            while (!line.isNull()) {
                if (line.startsWith(";")){
                    qDebug()<<line;
                    emit error(line);
                }
                line = in.readLine();
            }
        }
    }
    if (QFile(watchfolder+"out.done").exists()){
        qDebug("Done");
        emit done("out");
    }
}

void DVDCreator::startDVDJob(){
    createAviSynthFile("D:/RocketDVD/DSC_0453.AVI");
    createJobFile();
}
