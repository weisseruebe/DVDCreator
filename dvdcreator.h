#ifndef DVDCREATOR_H
#define DVDCREATOR_H

#include <QObject>
#include <QTime>
#include <QFileSystemWatcher>
#include <QHash>

#include "videofile.h"

class DVDCreator : public QObject
{
    Q_OBJECT

public:
    explicit DVDCreator(QString watchfolder, QString avsFolder, QString baseProject, QString menuTheme, QObject *parent = 0);
    void startDVDJob(QString id, QString title, QString subtitle, QList<VideoFile> videoFiles, QHash<QString, QString> parameters);

signals:
    void running(QString id);
    void done(QString id);
    void error(QString msg);

public slots:
    void handleFileChanges(QString path);
    void setMenuFile(QString menuThemePath);

private:
    void createJobFile(QString id, QString title, QString subtitle, QList<VideoFile> videoFiles, QHash<QString, QString> variables);
    void createAviSynthFile(QString avsFileName, VideoFile videofile);

    QString m_watchfolder;
    QString m_baseProjectPath;
    QString m_avsFolder;
    QString m_menuTheme;
    QString m_jobFileName;
    QFileSystemWatcher* watchFolderWatcher;
};

#endif // DVDCREATOR_H
