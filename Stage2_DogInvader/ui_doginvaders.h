/********************************************************************************
** Form generated from reading UI file 'doginvaders.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOGINVADERS_H
#define UI_DOGINVADERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DogInvaders
{
public:

    void setupUi(QDialog *DogInvaders)
    {
        if (DogInvaders->objectName().isEmpty())
            DogInvaders->setObjectName(QStringLiteral("DogInvaders"));
        DogInvaders->resize(400, 300);

        retranslateUi(DogInvaders);

        QMetaObject::connectSlotsByName(DogInvaders);
    } // setupUi

    void retranslateUi(QDialog *DogInvaders)
    {
        DogInvaders->setWindowTitle(QApplication::translate("DogInvaders", "DogInvaders", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DogInvaders: public Ui_DogInvaders {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOGINVADERS_H
