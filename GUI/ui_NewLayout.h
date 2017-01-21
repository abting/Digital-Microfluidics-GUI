/********************************************************************************
** Form generated from reading UI file 'NewLayout.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWLAYOUT_H
#define UI_NEWLAYOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewLayout
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *rowEdit;
    QLineEdit *columnEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Ok;
    QPushButton *Cancel;

    void setupUi(QDialog *NewLayout)
    {
        if (NewLayout->objectName().isEmpty())
            NewLayout->setObjectName(QStringLiteral("NewLayout"));
        NewLayout->resize(251, 217);
        horizontalLayout = new QHBoxLayout(NewLayout);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(NewLayout);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(NewLayout);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        rowEdit = new QLineEdit(NewLayout);
        rowEdit->setObjectName(QStringLiteral("rowEdit"));

        verticalLayout_2->addWidget(rowEdit);

        columnEdit = new QLineEdit(NewLayout);
        columnEdit->setObjectName(QStringLiteral("columnEdit"));

        verticalLayout_2->addWidget(columnEdit);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        Ok = new QPushButton(NewLayout);
        Ok->setObjectName(QStringLiteral("Ok"));

        horizontalLayout_3->addWidget(Ok);

        Cancel = new QPushButton(NewLayout);
        Cancel->setObjectName(QStringLiteral("Cancel"));

        horizontalLayout_3->addWidget(Cancel);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_3);


        retranslateUi(NewLayout);

        QMetaObject::connectSlotsByName(NewLayout);
    } // setupUi

    void retranslateUi(QDialog *NewLayout)
    {
        NewLayout->setWindowTitle(QApplication::translate("NewLayout", "Dialog", 0));
        label->setText(QApplication::translate("NewLayout", "Rows:", 0));
        label_2->setText(QApplication::translate("NewLayout", "Columns:", 0));
        Ok->setText(QApplication::translate("NewLayout", "OK", 0));
        Cancel->setText(QApplication::translate("NewLayout", "CANCEL", 0));
    } // retranslateUi

};

namespace Ui {
    class NewLayout: public Ui_NewLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWLAYOUT_H
