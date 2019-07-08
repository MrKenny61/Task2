#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QTextEdit>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile(const QString &filePath);
    void on_actionOpen_File_triggered();

    void saveFile(const QString &filePath);
    void on_actionSave_File_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
