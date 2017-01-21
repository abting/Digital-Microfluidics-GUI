#ifndef DROPLETSELECTOR_H
#define DROPLETSELECTOR_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QString>

namespace Ui {
class DropletSelector;
}

class DropletSelector : public QDialog
{
    Q_OBJECT

public:
    explicit DropletSelector(QWidget *parent = 0);
    ~DropletSelector();

    QString getName();
    QString getColor();
    double getVolume();
    bool Done = false;

private slots:
    void on_OK_clicked();
    void on_Cancel_clicked();

private:
    Ui::DropletSelector *ui;

    QString Name;
    QString Volume;
    QString Color;

    //widgets
    QLineEdit *NameEditor;
    QLineEdit *VolumeEditor;
    QComboBox *ColorSelector;
};

#endif // DROPLETSELECTOR_H
