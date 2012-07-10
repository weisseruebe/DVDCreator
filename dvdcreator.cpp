#include <QFile>
#include <QTextStream>
#include <QFileSystemWatcher>
#include <QDateTime>
#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QHash>
#include "dvdcreator.h"

DVDCreator::DVDCreator(QString watchfolder, QString avsFolder, QString baseProject, QString menuTheme, QObject *parent) :
    QObject(parent),m_watchfolder(watchfolder),m_baseProjectPath(baseProject),m_menuTheme(menuTheme),m_jobFileName("out")
{
    m_avsFolder = QDir::toNativeSeparators(avsFolder);
    qDebug() << m_avsFolder;

    watchFolderWatcher = new QFileSystemWatcher(this);
    watchFolderWatcher->addPath(watchfolder);

    connect(watchFolderWatcher,SIGNAL(fileChanged(QString)),this,SLOT(handleFileChanges(QString)));
    connect(watchFolderWatcher,SIGNAL(directoryChanged(QString)),this,SLOT(handleFileChanges(QString)));
}


void DVDCreator::startDVDJob(QString id, QString title, QString subtitle, QList<VideoFile> videoFiles, QHash<QString,QString> variables){
    m_jobFileName = id;
    QFile file(m_watchfolder+m_jobFileName+".txt");

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<< "JobTemplate = " << m_baseProjectPath << endl;
    out<< "JobID = " << id << endl;
    out<< "StartingStage = Transcode" << endl;
    out<< "Quantity = 1" << endl;
    out<< "Title = " << title << endl;
    out<< "Subtitle = " << subtitle << endl;
    out<< "Date = " << QDateTime::currentDateTime().toString() << endl;

    QHashIterator<QString, QString> i(variables);
    while (i.hasNext()) {
        i.next();
        out<<"Variable = " << i.key() << "," << i.value()<<endl;
    }
    out<< "MenuTheme=" << m_menuTheme << endl;
    out<< "UsePre-EncodedFiles=yes" << endl;
    out<< "Pre-EncodedFileType = FilesToEncode" << endl;

    int j = 0;
    foreach(VideoFile videoFile,videoFiles){
        QString avsFileName = m_avsFolder+id+QString::number(j++)+".avs";
        createAviSynthFile(avsFileName,videoFile);
        out << "Pre-CapturedFile=VIDEO:" << avsFileName << ",LENGTH:" << videoFile.m_length.toString("h:m:s") << ",TITLE:" <<  videoFile.m_name << endl;
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


void DVDCreator::setMenuFile(QString menuThemePath){
    m_menuTheme = menuThemePath;
}

void DVDCreator::handleFileChanges(QString path){
    if (QFile(path+m_jobFileName+".running").exists()){
        emit running(m_jobFileName);
    }
    if (QFile(path+m_jobFileName+".err").exists()){
        QFile file(path+m_jobFileName+".err");
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
    if (QFile(path+m_jobFileName+".done").exists()){
        emit done(m_jobFileName);
    }
}

