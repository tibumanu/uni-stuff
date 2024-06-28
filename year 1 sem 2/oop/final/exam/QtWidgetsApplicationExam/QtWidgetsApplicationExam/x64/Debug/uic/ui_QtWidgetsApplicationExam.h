/********************************************************************************
** Form generated from reading UI file 'QtWidgetsApplicationExam.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSAPPLICATIONEXAM_H
#define UI_QTWIDGETSAPPLICATIONEXAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplicationExamClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtWidgetsApplicationExamClass)
    {
        if (QtWidgetsApplicationExamClass->objectName().isEmpty())
            QtWidgetsApplicationExamClass->setObjectName("QtWidgetsApplicationExamClass");
        QtWidgetsApplicationExamClass->resize(600, 400);
        menuBar = new QMenuBar(QtWidgetsApplicationExamClass);
        menuBar->setObjectName("menuBar");
        QtWidgetsApplicationExamClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtWidgetsApplicationExamClass);
        mainToolBar->setObjectName("mainToolBar");
        QtWidgetsApplicationExamClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtWidgetsApplicationExamClass);
        centralWidget->setObjectName("centralWidget");
        QtWidgetsApplicationExamClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtWidgetsApplicationExamClass);
        statusBar->setObjectName("statusBar");
        QtWidgetsApplicationExamClass->setStatusBar(statusBar);

        retranslateUi(QtWidgetsApplicationExamClass);

        QMetaObject::connectSlotsByName(QtWidgetsApplicationExamClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtWidgetsApplicationExamClass)
    {
        QtWidgetsApplicationExamClass->setWindowTitle(QCoreApplication::translate("QtWidgetsApplicationExamClass", "QtWidgetsApplicationExam", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplicationExamClass: public Ui_QtWidgetsApplicationExamClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATIONEXAM_H
