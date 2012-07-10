#ifndef VIDEOFILE_H
#define VIDEOFILE_H

//#include <QObject>
#include <QTime>

class VideoFile //: public QObject
{
   // Q_OBJECT

public:
    explicit VideoFile(QString path, QString name, QTime length);
    QString m_path;
    QString m_name;
    QTime m_length;

    
//signals:
    
//public slots:
    
};

#endif // VIDEOFILE_H
