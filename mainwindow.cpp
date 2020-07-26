#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateDotFile();
    updateImage();
    renderImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDotFile()
{
    std::ofstream myFile;
    QDir::setCurrent(QCoreApplication::applicationFilePath());
    myFile.open
    (
        "file.dot"
    );

    std::string textToFile = radixTree.getDotFileModeOne();

    myFile << textToFile;
    myFile.close();
}

void MainWindow::updateImage()
{
    std::string message =
                "dot -Tpng file.dot > file.png";
    QDir::setCurrent(QCoreApplication::applicationFilePath());
    system(message.c_str());
}

void MainWindow::renderImage()
{
    QDir::setCurrent(QCoreApplication::applicationFilePath());
    QPixmap image("file.png");
    ui->labelOfImage->setPixmap(image);
    ui->labelOfImage->show();
}

void MainWindow::on_pushButtonOfInsert_clicked()
{
    QString toInsert = ui->lineEditOfInsert->text();

    bool ret = radixTree.insert(toInsert.toStdString());

    updateDotFile();
    updateImage();
    renderImage();

    QMessageBox msgBox;
    if (ret)
        msgBox.setText("The word was inserted");
    else
        msgBox.setText("This word already exists in the tree");
    msgBox.exec();
}

void MainWindow::on_pushButtonOfSearch_clicked()
{
    QString toInsert = ui->lineEditOfSearch->text();
    RadixNode* ret = radixTree.search(toInsert.toStdString());

    updateDotFile();
    updateImage();
    renderImage();

    QMessageBox msgBox;
    if (ret)
        msgBox.setText("This word exists");
    else
        msgBox.setText("This word does not exists");
    msgBox.exec();
}

void MainWindow::on_pushButtonOfRemove_clicked()
{
    QString toIntoRemovesert = ui->lineEditOfRemove->text();
    bool ret = radixTree.remove(toIntoRemovesert.toStdString());

    updateDotFile();
    updateImage();
    renderImage();

    QMessageBox msgBox;
    if (ret)
        msgBox.setText("The word was removed");
    else
        msgBox.setText("This word does not exists");
    msgBox.exec();
}
