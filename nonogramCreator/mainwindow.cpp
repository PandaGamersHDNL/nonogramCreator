#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //have a settings panel on start up
    // import an exported file not image?
    // option to start again/ redefine grid in editing
    // color option of squares
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //qDebug() << ui->stackedWidget->count();
    auto gridNum = this->ui->gridNumber->value();
    this->grid = new Nonogram(this, gridNum);
    this->ui->stackedWidget->addWidget(this->grid);
    auto newIndex = this->ui->stackedWidget->indexOf(this->grid);
    //qDebug() << ui->stackedWidget->currentIndex();
    this->ui->stackedWidget->setCurrentIndex(newIndex);
}


void MainWindow::on_actionexport_triggered()
{
    qDebug() << "export activated";
    if(this->grid){
        qDebug() << "grid available";
        this->grid->exportSelf();
    }
}


void MainWindow::on_actionimport_triggered()
{
    qDebug() << "import activated";
    if(this->grid){
        //remove/ remove stack of staccked widget
    }
    QString dir;
    auto filename = QFileDialog::getOpenFileName(this, "select a nonogram file (.nono", dir, "*.nono");
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    if(file.exists()){
        qDebug() << "File exists";
        this->grid = new Nonogram(&file, this);
        this->ui->stackedWidget->addWidget(this->grid);
        auto newIndex = this->ui->stackedWidget->indexOf(this->grid);

        qDebug() << ui->stackedWidget->currentIndex();
        this->ui->stackedWidget->setCurrentIndex(newIndex);
         qDebug() << ui->stackedWidget->currentIndex();
    }

}


void MainWindow::on_actionnew_triggered()
{
    this->ui->stackedWidget->removeWidget(grid);
    this->grid->deleteLater();
    this->ui->stackedWidget->setCurrentIndex(0);

}

