#include <QFile>
#include <QTextStream>
#include <QFileSystemWatcher>
#include <QDateTime>
#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QHash>
#include "dvdcreator.h"

DVDCreator::DVDCreator(QObject *parent) :
    QObject(parent)
{
    watchfolder = "D:/RocketDVD/watchfolder/";
    avsPath = "D:\\RocketDVD\\direct.avs";
    baseProjectPath = "D:/RocketDVD/test.prj";
    menuTheme = "C:/Programme/Digital Media Applications/RocketDVD Professional Trial/Menu/CORPORATE - insert your own titles_PAL_MWA.menu";
    jobFileName = "out";

    watchFolderWatcher = new QFileSystemWatcher(this);
    watchFolderWatcher->addPath(watchfolder);

    connect(watchFolderWatcher,SIGNAL(fileChanged(QString)),this,SLOT(handleFileChanges(QString)));
    connect(watchFolderWatcher,SIGNAL(directoryChanged(QString)),this,SLOT(handleFileChanges(QString)));

}


void DVDCreator::createJobFile(QString id, QString title, QString subtitle, QTime length, QHash<QString,QString> variables){
    jobFileName = id;
    QFile file(watchfolder+jobFileName+".txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<"JobTemplate = "<<baseProjectPath<<endl;
    out<<"JobID = "<<id<<endl;
    out<<"StartingStage = Transcode" << endl;

    out<<"Title = "<<title<<endl;
    out<<"Subtitle = "<<subtitle<<endl;
    out<<"Date = "<<QDateTime::currentDateTime().toString()<<endl;

    QHashIterator<QString, QString> i(variables);
    while (i.hasNext()) {
        i.next();
        out<<"Variable = " << i.key() << "," << i.value()<<endl;
    }
    out<<"MenuTheme="<<menuTheme<<endl;
    out<<"UsePre-EncodedFiles=yes"<<endl;
    out<<"Pre-EncodedFileType = FilesToEncode"<<endl;
    out<<"Pre-CapturedFile=VIDEO:"<<avsPath<<",LENGTH:"<<length.toString("h:m:s")<<",TITLE:Demo"<<endl;

    file.close();
}

void DVDCreator::createAviSynthFile(QString videofile, bool resize = true, bool crop = false, bool changeFps = true){
    QFile file(avsPath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<"DirectShowSource(\""<<videofile<<"\")" << endl;
    if (changeFps){
        out<<"AssumeFPS(25)"<<endl;
    }
    if (crop){
        out << "Crop(160, 0, 960, 720)" << endl;
    }
    if (resize){
        out<<"LanczosResize(720, 576)" << endl;
    }
    file.close();
}


void DVDCreator::setMenuFile(QString path){
    menuTheme = path;
}

void DVDCreator::handleFileChanges(QString path){
    if (QFile(path+jobFileName+".running").exists()){
        emit running(jobFileName);
    }
    if (QFile(path+jobFileName+".err").exists()){
        QFile file(path+jobFileName+".err");
        QString errorMessage;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            QString line = in.readLine();
            while (!line.isNull()) {
                if (line.startsWith(";")){
                    errorMessage.append(line);
                }
                line = in.readLine();
            }
            emit error(errorMessage);
        }
    }
    if (QFile(path+jobFileName+".done").exists()){
        emit done(jobFileName);
    }
}

void DVDCreator::startDVDJob(QString id, QString title, QString subtitle, QString videoFile, QTime length, QHash<QString, QString> parameters){
    createAviSynthFile(videoFile);
    createJobFile(id, title, subtitle, length, parameters);
}
