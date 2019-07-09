#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file.h"
#include "student.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->showMessage("OK");
    Student_model *studmod = new Student_model;
    ui->tableView->setModel(studmod);
}

MainWindow::~MainWindow()
{
    delete ui;
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

    QDataStream input(&mFile);
    Student_model::student stud;
    Student_model *studmod = new Student_model;

    while(true)
    {
        input >> stud;
        studmod->vector.push_back(stud);
        if (input.atEnd()) break;
    }

    ui->tableView->setModel(studmod);
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

    QDataStream output(&mFile);

    Student_model::student stud;
    QModelIndex index;
    int size = ui->tableView->model()->rowCount();
    for( int i=0; i<size;i++)
    {
        index= ui->tableView->model()->index(i,0);
        stud.name = ui->tableView->model()->data(index,Qt::DisplayRole).toString();
        index= ui->tableView->model()->index(i,1);
        stud.course= ui->tableView->model()->data(index,Qt::DisplayRole).toUInt();
        index= ui->tableView->model()->index(i,2);
        stud.group= ui->tableView->model()->data(index,Qt::DisplayRole).toUInt();
        output<<stud;
    }

    ui->statusBar->showMessage("Write to file: " + filePath);
    mFile.close();
}

void MainWindow::on_insButton_clicked()
{
    QModelIndex cur = ui->tableView->currentIndex();
    ui->tableView->model()->insertRows(1,1,cur);
}

void MainWindow::on_delButton_clicked()
{
    QModelIndex current=ui->tableView->currentIndex();

    if( ui->tableView->model()->rowCount()!=1)
    ui->tableView->model()->removeRows(1,1,current);
}
