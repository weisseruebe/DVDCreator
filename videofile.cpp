#include "videofile.h"

VideoFile::VideoFile(QString path, QString name, QTime length, int sourceFps, bool resize, bool crop) :
    m_path(path),m_name(name),m_length(length),m_sourceFps(sourceFps),m_resize(resize),m_crop(crop)
{

}


VideoFile::VideoFile(QString path, QString name, QTime length) :
    m_path(path),m_name(name),m_length(length),m_sourceFps(25),m_resize(true),m_crop(false)
{

}
