#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QListWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addButton,SIGNAL(released()),this,SLOT(addTask()));
    connect(ui->exportButton,SIGNAL(released()),this,SLOT(exportList()));
    connect(ui->importButton,SIGNAL(released()),this,SLOT(importList()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void::MainWindow::addTask(){
    QString itemText = ui->input->text();
    QWidget *itemWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(itemWidget);

    QLabel *label = new QLabel(itemText,itemWidget);
    layout->addWidget(label);

    QCheckBox *checkBox = new QCheckBox("Done?",itemWidget);
    layout->addWidget(checkBox);

    QPushButton *editButton = new QPushButton("Edit",itemWidget);
    layout->addWidget(editButton);

    QPushButton *removeButton = new QPushButton("Remove",itemWidget);
    layout->addWidget(removeButton);

    itemWidget->setLayout(layout);

    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(item);

    ui->listWidget->setItemWidget(item,itemWidget);
    ui->listWidget->setStyleSheet("QListWidget::item { height: 50px; }");

    QPushButton *button = qobject_cast<QPushButton*>(sender());

    connect(removeButton, &QPushButton::clicked, this, [this, item]() {
        int row = ui->listWidget->row(item);
        ui->listWidget->takeItem(row);
    });

    connect(editButton, &QPushButton::clicked, this, [this, label, itemWidget]() {
        QLineEdit *lineEdit = new QLineEdit(label->text(), itemWidget);
        itemWidget->layout()->replaceWidget(label,lineEdit);
        lineEdit->selectAll();
        lineEdit->setFont(QFont("Segoe UI", 16));
        lineEdit->setFocus();

        connect(lineEdit, &QLineEdit::editingFinished, this, [this, lineEdit, label, itemWidget](){
            label->setText(lineEdit->text());
            itemWidget->layout()->replaceWidget(lineEdit,label);
            delete lineEdit;
        });
    });
    ui->input->clear();
}

void::MainWindow::exportList(){
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString filename = QFileDialog::getSaveFileName(this, "Save List","tasks_" + timestamp + ".txt","Text files (*.txt)");

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Could not open file for writing!";
        return;
    }

    QTextStream out(&file);

    for(int i = 0; i<ui->listWidget->count();i++){
        QListWidgetItem *item = ui->listWidget->item(i);
        QWidget *itemWidget = ui->listWidget->itemWidget(item);

        if(!itemWidget) continue;

        QLineEdit *lineEdit = itemWidget->findChild<QLineEdit *>();
        QLabel *label = itemWidget->findChild<QLabel *>();
        QCheckBox *checkBox = itemWidget->findChild<QCheckBox *>();

        QString taskText;
        QString taskStatus;
        if(lineEdit) taskText = lineEdit->text();
        else if(label) taskText = label->text();
        else taskText = "Unknown task";

        if(checkBox->isChecked()) taskStatus = "[DONE]";
        else taskStatus = "[TO DO]";

        out << taskStatus << " " << taskText << "\n";
    }
    file.close();
}

void::MainWindow::importList(){
    QString filename = QFileDialog::getOpenFileName(this,"Open Task List","","Text files (*.txt)");

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Could not open file for writing!";
        return;
    }

    QTextStream in(&file);
    ui->listWidget->clear();

    while(!in.atEnd()){
        QString line = in.readLine();
        if(line.isEmpty()) continue;

        int endBracketIndex = line.indexOf(']');
        if (endBracketIndex == -1) {
            continue;
        }

        QString taskStatus = line.left(endBracketIndex + 1);
        QString taskText = line.mid(endBracketIndex + 2);

        QWidget *itemWidget = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout(itemWidget);

        QLineEdit *lineEdit = new QLineEdit(taskText, itemWidget);
        layout->addWidget(lineEdit);

        QCheckBox *checkBox = new QCheckBox("Done?",itemWidget);
        checkBox->setChecked(taskStatus == "[DONE]");
        layout->addWidget(checkBox);


        QPushButton *editButton = new QPushButton("Edit", itemWidget);
        layout->addWidget(editButton);

        QPushButton *removeButton = new QPushButton("Remove", itemWidget);
        layout->addWidget(removeButton);

        itemWidget->setLayout(layout);

        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setSizeHint(itemWidget->sizeHint());
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, itemWidget);

        connect(removeButton, &QPushButton::clicked, this, [this, item]() {
            delete ui->listWidget->takeItem(ui->listWidget->row(item));
        });

        connect(editButton, &QPushButton::clicked, this, [this, lineEdit]() {
            lineEdit->setFocus();
            lineEdit->selectAll();
        });
    }
    file.close();
}
