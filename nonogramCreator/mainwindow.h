#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nonogram.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Nonogram* grid;

private slots:
    void on_pushButton_clicked();


    void on_actionexport_triggered();

    void on_actionimport_triggered();

    void on_actionnew_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
