#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("OK");
    connect(ui->insButton, SIGNAL(clicked()), SLOT(insRow()));
    connect(ui->delButton, SIGNAL(clicked()), SLOT(delRow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void insRow()
{

}

void delRow()
{

}

void MainWindow::on_actionOpen_File_triggered()
{
    File *wnd = new File(this);
    wnd->show();

    connect(wnd, SIGNAL(filePath(QString)), this, SLOT(openFile(QString)));
}

void MainWindow::openFile(const QString &filePath)
{
    QFile mFile(filePath);
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this, "Error", "Error open file");
        ui->statusBar->showMessage("Error open file");
        return;
    }
    QTextStream stream(&mFile);
    //QString buffer = stream.readAll();
    //ui->tableView
    ui->statusBar->showMessage("Read to file: " + filePath);
    mFile.flush();
    mFile.close();
}

void MainWindow::on_actionSave_File_triggered()
{
    File *wnd = new File(this);
    wnd->show();

    connect(wnd, SIGNAL(filePath(QString)), this, SLOT(saveFile(QString)));
}

void MainWindow::saveFile(const QString &filePath)
{
    QFile mFile(filePath);
    if(!mFile.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(this, "Error", "Error save file");
        ui->statusBar->showMessage("Error save file");
        return;
    }
    QTextStream stream(&mFile);
    stream<<ui->tableView->Plain;
    ui->statusBar->showMessage("Write to file: " + filePath);
    mFile.close();
}
