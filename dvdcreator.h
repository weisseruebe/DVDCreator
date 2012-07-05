#ifndef DVDCREATOR_H
#define DVDCREATOR_H

#include <QObject>

class DVDCreator : public QObject
{
    Q_OBJECT
public:
    explicit DVDCreator(QObject *parent = 0);
    void createJobFile();
    void createAviSynthFile();
signals:

public slots:

private:
    QString watchfolder;
    QString baseProjectPath;
    QString avsPath;
    QString menuTheme;

};

#endif // DVDCREATOR_H
