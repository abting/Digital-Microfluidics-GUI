#include "PathHandler.h"
#include "Droplet.h"

PathHandler::PathHandler()
{

}

PathHandler::PathHandler(QStringList pList)
{
    foreach(QString pos, pList){
        pathList.append(pos);
    }

}

//KIWI
PathHandler::PathHandler(QList <Droplet*> dList)
{
    foreach(Droplet* drop, dList){
        dropletList.append(drop);
    }

}

void PathHandler::setdropletList(QList <Droplet*> dropList)
{
    foreach(Droplet* drop, dropList){
        dropletList.append(drop);
    }
}

QList <Droplet*> PathHandler::getdropletList()
{
    return dropletList;
}


void PathHandler::setPathList()
{
    if(dropletList.isEmpty()){

    }
    else{
        foreach(Droplet* drop, dropletList){
            for (int i = 0; i<drop->getDropletInfo().length(); i++){
                if(i>=pathList.length()){
                    pathList.append(drop->getDropletInfo().at(i).position);
                }
                else{
                    pathList[i] += "," + drop->getDropletInfo().at(i).position;
                }
            }
        }
    }
}

void PathHandler::setPathListEmode(Table* tableEmode){
    //QStringList elecPath;
    for (int j =1; j<tableEmode->getColumn();j++){
        QString pos = "";
        for(int i = 2; i<tableEmode->getRow(); i++){
            if(tableEmode->getItem(i,j)){
                pos += tableEmode->getItem(i,j)->text() + ",";
            }
        }
        pathList.append(pos);
    }

}
QStringList PathHandler::getPathList()
{
    return pathList;
}



void PathHandler::savePath(QMainWindow *layout){
    QString fileName = QFileDialog::getSaveFileName(layout,QObject::tr("Save File"),"","Text Files (*.txt)");
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream outStream(&file);
    for(int i = 0; i<pathList.length();i++){
        outStream << pathList.at(i);
        outStream << endl;
    }
    file.close();
}


void PathHandler::openPath(QMainWindow *layout){

    pathList.clear();
    QString fileName = QFileDialog::getOpenFileName(layout,QObject::tr("Open Design"), "", "Text Files (*.txt)");
    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QTextStream inStream(&file);
    //bool firstLine = true;
    //int at_row=0;
    while(!inStream.atEnd()){
        QString line = inStream.readLine();
        pathList.append(line);
        //QStringList list = line.split(",");
//        if(firstLine){
//          rows = list.at(0).toInt();
//          columns = list.at(1).toInt();
//            std::cout<<rows;
//            std::cout<<columns;
//            firstLine = false;
//        }
//        else{
//        }
    }
   file.close();


}
