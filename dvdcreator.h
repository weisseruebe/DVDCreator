#ifndef DVDCREATOR_H
#define DVDCREATOR_H

#include <QObject>
#include <QTime>
#include <QFileSystemWatcher>
#include <QHash>

class DVDCreator : public QObject
{
    Q_OBJECT

public:
    explicit DVDCreator(QObject *parent = 0);
    void createJobFile(QString id, QString title, QString subtitle, QTime length, QHash<QString, QString> variables);
    void createAviSynthFile(QString videofile, bool resize, bool crop, bool changeFps);
    void startDVDJob(QString id, QString videoFile);

signals:
    void running(QString id);
    void done(QString id);
    void error(QString msg);

public slots:
    void handleFileChanges(QString path);
    void setMenuFile(QString path);

private:
    QString watchfolder;
    QString baseProjectPath;
    QString avsPath;
    QString menuTheme;
    QString jobFileName;
    QFileSystemWatcher* watchFolderWatcher;
};

#endif // DVDCREATOR_H
