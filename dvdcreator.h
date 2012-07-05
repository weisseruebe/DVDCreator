#ifndef DVDCREATOR_H
#define DVDCREATOR_H

#include <QObject>
#include <QFileSystemWatcher>

class DVDCreator : public QObject
{
    Q_OBJECT

public:
    explicit DVDCreator(QObject *parent = 0);
    void createJobFile();
    void createAviSynthFile(bool resize, bool changeFps);
    void startDVDJob();

signals:

public slots:
    void handleFileChanges(QString path);

private:
    QString watchfolder;
    QString baseProjectPath;
    QString avsPath;
    QString menuTheme;
    //QFileSystemWatcher* watchFolderWatcher;
};

#endif // DVDCREATOR_H
