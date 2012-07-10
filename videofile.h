/*!
  ** \file videofile.h
  ** \date July 2012
  ** \author Andreas Rettig
  ***************************************************/

#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include <QTime>

/*!
  ** A very simple container class for a videoFile and the needed metadata for authoring
  **
  *****************************************************************************************/

class VideoFile
{

public:
    VideoFile(QString path, QString name, QTime length, bool changeFps, bool resize, bool crop);
    VideoFile(QString path, QString name, QTime length);
    QString m_path;
    QString m_name;
    QTime m_length;
    bool m_changeFps;
    bool m_crop;
    bool m_resize;
    
};

#endif // VIDEOFILE_H
