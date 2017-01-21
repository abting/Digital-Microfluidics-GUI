#ifndef PATHHANDLER_H
#define PATHHANDLER_H
#include <iostream>
using namespace std;
#include <Droplet.h>


struct PathInfo
{
   QString electrodes;
   int time;
};

class PathHandler
{
public:
    PathHandler();
    //KIWI
    PathHandler(QList <Droplet*>);
    void savePath();
    void openPath();
    void previewPath();
    void setdropletList(QList <Droplet*>);
    QList <Droplet*> getdropletList();
    void setPathList();
    QStringList getPathList();


    void savedropletpath(); //txt
    void opensavedpath();   //txt



private:
    //KIWI
    QList <Droplet*> dropletList;
    QStringList pathList;
};

#endif // PATHHANDLER_H
