/********************************************************************************
** Form generated from reading UI file 'DropletSelector.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DROPLETSELECTOR_H
#define UI_DROPLETSELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DropletSelector
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *volumedit;
    QLabel *coloredit;
    QVBoxLayout *verticalLayout;
    QLineEdit *nameedit;
    QLineEdit *voledit;
    QComboBox *colorbox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *OK;
    QPushButton *Cancel;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *DropletSelector)
    {
        if (DropletSelector->objectName().isEmpty())
            DropletSelector->setObjectName(QStringLiteral("DropletSelector"));
        DropletSelector->resize(302, 156);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DropletSelector->sizePolicy().hasHeightForWidth());
        DropletSelector->setSizePolicy(sizePolicy);
        DropletSelector->setMaximumSize(QSize(302, 156));
        horizontalLayout_3 = new QHBoxLayout(DropletSelector);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(DropletSelector);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        volumedit = new QLabel(DropletSelector);
        volumedit->setObjectName(QStringLiteral("volumedit"));

        verticalLayout_2->addWidget(volumedit);

        coloredit = new QLabel(DropletSelector);
        coloredit->setObjectName(QStringLiteral("coloredit"));

        verticalLayout_2->addWidget(coloredit);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        nameedit = new QLineEdit(DropletSelector);
        nameedit->setObjectName(QStringLiteral("nameedit"));

        verticalLayout->addWidget(nameedit);

        voledit = new QLineEdit(DropletSelector);
        voledit->setObjectName(QStringLiteral("voledit"));

        verticalLayout->addWidget(voledit);

        colorbox = new QComboBox(DropletSelector);
        colorbox->setObjectName(QStringLiteral("colorbox"));

        verticalLayout->addWidget(colorbox);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        OK = new QPushButton(DropletSelector);
        OK->setObjectName(QStringLiteral("OK"));

        horizontalLayout_2->addWidget(OK);

        Cancel = new QPushButton(DropletSelector);
        Cancel->setObjectName(QStringLiteral("Cancel"));

        horizontalLayout_2->addWidget(Cancel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_3);

        QWidget::setTabOrder(nameedit, voledit);
        QWidget::setTabOrder(voledit, colorbox);

        retranslateUi(DropletSelector);

        QMetaObject::connectSlotsByName(DropletSelector);
    } // setupUi

    void retranslateUi(QDialog *DropletSelector)
    {
        DropletSelector->setWindowTitle(QApplication::translate("DropletSelector", "Dialog", 0));
        label->setText(QApplication::translate("DropletSelector", "Name:", 0));
        volumedit->setText(QApplication::translate("DropletSelector", "Volume (micro):", 0));
        coloredit->setText(QApplication::translate("DropletSelector", "Color:", 0));
        OK->setText(QApplication::translate("DropletSelector", "OK", 0));
        Cancel->setText(QApplication::translate("DropletSelector", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class DropletSelector: public Ui_DropletSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DROPLETSELECTOR_H
