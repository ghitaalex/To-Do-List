/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *listWidget;
    QLineEdit *input;
    QPushButton *addButton;
    QLabel *label;
    QPushButton *importButton;
    QPushButton *exportButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(40, 150, 501, 361));
        QFont font;
        font.setPointSize(16);
        listWidget->setFont(font);
        listWidget->setSpacing(3);
        input = new QLineEdit(centralwidget);
        input->setObjectName("input");
        input->setGeometry(QRect(40, 70, 501, 51));
        input->setFont(font);
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(572, 68, 101, 51));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 10, 221, 41));
        QFont font1;
        font1.setPointSize(20);
        label->setFont(font1);
        importButton = new QPushButton(centralwidget);
        importButton->setObjectName("importButton");
        importButton->setGeometry(QRect(570, 150, 101, 51));
        exportButton = new QPushButton(centralwidget);
        exportButton->setObjectName("exportButton");
        exportButton->setGeometry(QRect(570, 240, 101, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "To-Do List", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "To-Do List App", nullptr));
        importButton->setText(QCoreApplication::translate("MainWindow", "Import List", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "Export List", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
