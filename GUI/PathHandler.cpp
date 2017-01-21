#include "PathHandler.h"
#include "Droplet.h"

PathHandler::PathHandler()
{

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
QStringList PathHandler::getPathList()
{
    return pathList;
}
