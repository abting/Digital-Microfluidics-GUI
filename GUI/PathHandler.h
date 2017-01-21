#ifndef PATHHANDLER_H
#define PATHHANDLER_H
#include <iostream>
using namespace std;
#include <Droplet.h>
#include <QMainWindow>
#include <QFileDialog>

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
    void savePath(QMainWindow*);
    void openPath(QMainWindow*);
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
