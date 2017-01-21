#ifndef NEWLAYOUT_H
#define NEWLAYOUT_H

#include <QDialog>

namespace Ui {
class NewLayout;
}

class NewLayout : public QDialog
{
    Q_OBJECT

public:
    explicit NewLayout(QWidget *parent = 0);
    ~NewLayout();

    int getColumns();
    int getRows();

private slots:
    void on_Ok_clicked();
    void on_Cancel_clicked();

private:
    Ui::NewLayout *ui;
    int Columns;
    int Rows;
};

#endif // NEWLAYOUT_H
