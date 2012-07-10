#ifndef VIDEOFILE_H
#define VIDEOFILE_H

//#include <QObject>
#include <QTime>

class VideoFile //: public QObject
{
   // Q_OBJECT

public:
    VideoFile(QString path, QString name, QTime length, bool changeFps, bool resize, bool crop);
    VideoFile(QString path, QString name, QTime length);
    QString m_path;
    QString m_name;
    QTime m_length;
    bool m_changeFps;
    bool m_crop;
    bool m_resize;

    
//signals:
    
//public slots:
    
};

#endif // VIDEOFILE_H
