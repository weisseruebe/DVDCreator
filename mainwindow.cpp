#include <QFileSystemWatcher>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dvdcreator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    creator = new DVDCreator();
    connect(creator,SIGNAL(running(QString)),this,SLOT(showRunning(QString)));
    connect(creator,SIGNAL(done(QString)),this,SLOT(showDone(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    creator->startDVDJob();
}

void MainWindow::showRunning(QString id){
    ui->progressBar->setMaximum(0);
}

void MainWindow::showDone(QString id){
    ui->progressBar->setMaximum(1);
    ui->progressBar->setValue(1);
}

void MainWindow::showError(QString msg){

}
