#include "media_thread.h"
#include <QtCore>

Media_thread::Media_thread(QObject *parent) : QThread(parent)
{

}

void Media_thread::run()
{
    QDirIterator it("C://", QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);
    QDirIterator it1("C://", QStringList() << "*.mp4", QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext() || it1.hasNext())
    {
        if(it.next()!=NULL)
        {
            qDebug() << it.next();
            emit get_available_media(it.next());
        }
        if(it1.next()!=NULL)
        {
            qDebug() << it1.next();
            emit get_available_media(it1.next());
        }
    }
}
