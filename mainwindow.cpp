#include <QFileSystemWatcher>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dvdcreator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFileSystemWatcher* watchFolderWatcher = new QFileSystemWatcher();
    watchFolderWatcher->addPath("D:/RocketDVD/watchfolder/");
    connect(watchFolderWatcher,SIGNAL(fileChanged(QString)),this,SLOT(handleFileChanges(QString)));
    connect(watchFolderWatcher,SIGNAL(directoryChanged(QString)),this,SLOT(handleFileChanges(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    DVDCreator creator;
    creator.startDVDJob();
}

void MainWindow::handleFileChanges(QString path){
    qDebug("HUUUU");
    qDebug(path.toAscii());
}
