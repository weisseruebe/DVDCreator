#include "videofile.h"

VideoFile::VideoFile(QString path, QString name, QTime length, bool changeFps, bool resize, bool crop) :
    m_path(path),m_name(name),m_length(length),m_changeFps(changeFps),m_resize(resize),m_crop(crop)
{

}


VideoFile::VideoFile(QString path, QString name, QTime length) :
    m_path(path),m_name(name),m_length(length),m_changeFps(true),m_resize(true),m_crop(true)
{

}
