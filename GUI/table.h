#ifndef TABLE_H
#define TABLE_H
#include <QTableWidget>
#include <QMainWindow>
#include <Droplet.h>


class Table : public QTableWidget
{
public:
    Table();
    Table(QTableWidget*);
    void CreateTable(QMainWindow*);
    void addDropToTable(Droplet*, QList <Droplet*>, int);
    void removeDropFromTable(Droplet*);
    void updateTable(Electrode *, int);
    QSlider* getSlider();
    int getColumn();
    int getRow();
    void setColumn(int);
    void setRow(int);
    void setSp(int, int, int, int);
    void setColumnW(int , int);
    void updateTableEmode(QString, Electrode*);
    void InitializeTableEmode(QMainWindow*);
    void setItem(int , int , QTableWidgetItem*);
    QTableWidgetItem* getItem(int , int);

private:
    int rows;
    int columns;
    QTableWidget* table;
    QSlider* slide;


};

#endif // TABLE_H
