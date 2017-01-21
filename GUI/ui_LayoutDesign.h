/********************************************************************************
** Form generated from reading UI file 'LayoutDesign.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYOUTDESIGN_H
#define UI_LAYOUTDESIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LayoutDesign
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *LeftFrame;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *TopFrame;
    QGridLayout *DesignGrid;
    QGridLayout *BottomFrame;
    QVBoxLayout *ActionFrame;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout;
    QPushButton *CreateButton;
    QPushButton *AcceptButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *LayoutDesign)
    {
        if (LayoutDesign->objectName().isEmpty())
            LayoutDesign->setObjectName(QStringLiteral("LayoutDesign"));
        LayoutDesign->setWindowModality(Qt::NonModal);
        LayoutDesign->resize(1149, 734);
        horizontalLayout = new QHBoxLayout(LayoutDesign);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        LeftFrame = new QGridLayout();
        LeftFrame->setObjectName(QStringLiteral("LeftFrame"));

        verticalLayout_3->addLayout(LeftFrame);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        TopFrame = new QGridLayout();
        TopFrame->setObjectName(QStringLiteral("TopFrame"));

        verticalLayout_2->addLayout(TopFrame);

        DesignGrid = new QGridLayout();
        DesignGrid->setObjectName(QStringLiteral("DesignGrid"));

        verticalLayout_2->addLayout(DesignGrid);

        BottomFrame = new QGridLayout();
        BottomFrame->setObjectName(QStringLiteral("BottomFrame"));

        verticalLayout_2->addLayout(BottomFrame);


        horizontalLayout->addLayout(verticalLayout_2);

        ActionFrame = new QVBoxLayout();
        ActionFrame->setObjectName(QStringLiteral("ActionFrame"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        ActionFrame->addItem(verticalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        CreateButton = new QPushButton(LayoutDesign);
        CreateButton->setObjectName(QStringLiteral("CreateButton"));
        CreateButton->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateButton->sizePolicy().hasHeightForWidth());
        CreateButton->setSizePolicy(sizePolicy);
        CreateButton->setStyleSheet(QStringLiteral("background-color: rgb(16, 173, 5);"));

        verticalLayout->addWidget(CreateButton);

        AcceptButton = new QPushButton(LayoutDesign);
        AcceptButton->setObjectName(QStringLiteral("AcceptButton"));
        AcceptButton->setEnabled(true);
        sizePolicy.setHeightForWidth(AcceptButton->sizePolicy().hasHeightForWidth());
        AcceptButton->setSizePolicy(sizePolicy);
        AcceptButton->setStyleSheet(QStringLiteral("background-color: rgb(16, 173, 5);"));

        verticalLayout->addWidget(AcceptButton);


        ActionFrame->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        ActionFrame->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(ActionFrame);

        AcceptButton->raise();
        CreateButton->raise();

        retranslateUi(LayoutDesign);

        QMetaObject::connectSlotsByName(LayoutDesign);
    } // setupUi

    void retranslateUi(QDialog *LayoutDesign)
    {
        LayoutDesign->setWindowTitle(QApplication::translate("LayoutDesign", "DesignLayout", 0));
        CreateButton->setText(QApplication::translate("LayoutDesign", "Create", 0));
        AcceptButton->setText(QApplication::translate("LayoutDesign", "Accept", 0));
    } // retranslateUi

};

namespace Ui {
    class LayoutDesign: public Ui_LayoutDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYOUTDESIGN_H
