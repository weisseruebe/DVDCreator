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
    /* The folder that is set as watchfolder in RocketDVD*/
    watchfolder = "D:/RocketDVD/watchfolder/";

    /*The path and name of the avisynth skript*/
    avsFolder = "D:\\RocketDVD\\";

    baseProjectPath = "D:/RocketDVD/test.prj";
    menuTheme = "C:/Programme/Digital Media Applications/RocketDVD Professional Trial/Menu/CORPORATE - insert your own titles_PAL_MWA.menu";
    jobFileName = "out";

    watchFolderWatcher = new QFileSystemWatcher(this);
    watchFolderWatcher->addPath(watchfolder);

    connect(watchFolderWatcher,SIGNAL(fileChanged(QString)),this,SLOT(handleFileChanges(QString)));
    connect(watchFolderWatcher,SIGNAL(directoryChanged(QString)),this,SLOT(handleFileChanges(QString)));

}


void DVDCreator::createJobFile(QString id, QString title, QString subtitle, QList<VideoFile> videoFiles, QHash<QString,QString> variables){
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

    int j = 0;
    foreach(VideoFile videoFile,videoFiles){
        QString avsFileName = avsFolder+id+QString::number(j++)+".avs";
        createAviSynthFile(avsFileName,videoFile);
        out<<"Pre-CapturedFile=VIDEO:"<<avsFileName<<",LENGTH:"<<videoFile.m_length.toString("h:m:s")<<",TITLE:"<<videoFile.m_name<<endl;
    }
    file.close();
}

void DVDCreator::createAviSynthFile(QString avsFileName, VideoFile videofile){
    QFile file(avsFileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out<<"DirectShowSource(\""<<videofile.m_path<<"\")" << endl;
        if (videofile.m_changeFps){
            out<<"AssumeFPS(25)"<<endl;
        }
        if (videofile.m_crop){
            out << "Crop(160, 0, 960, 720)" << endl;
        }
        if (videofile.m_resize){
            out<<"LanczosResize(720, 576)" << endl;
        }
        file.close();
    }
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

void DVDCreator::startDVDJob(QString id, QString title, QString subtitle, QList<VideoFile> videoFiles, QHash<QString, QString> parameters){
    createJobFile(id, title, subtitle, videoFiles, parameters);
}
