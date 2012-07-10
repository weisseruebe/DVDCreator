#include <QFileSystemWatcher>
#include <QMessageBox>
#include <QFileDialog>


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dvdcreator.h"
#include "videofile.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    creator = new DVDCreator("D:/RocketDVD/watchfolder/","D:\\RocketDVD\\", "D:/RocketDVD/test.prj","C:/Programme/Digital Media Applications/RocketDVD Professional Trial/Menu/CORPORATE - insert your own titles_PAL_MWA.menu");
    connect(creator,SIGNAL(running(QString)),this,SLOT(showRunning(QString)));
    connect(creator,SIGNAL(done(QString)),this,SLOT(showDone(QString)));
    connect(creator,SIGNAL(error(QString)),this,SLOT(showError(QString)));
    ui->pushButton->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QHash<QString,QString> parameters;
    parameters.insert("[[Company Name]]", "MWA");
    parameters.insert("[[Company Website]]", "www.mwa.com");
    parameters.insert("[[Company Telephone Number]]", "(030)123456");

    QList<VideoFile> videoFiles;

    foreach(QString fileName,fileNames){
        videoFiles<<VideoFile(fileName,"Holla",QTime(0,1,0));
    }
    creator->startDVDJob(ui->lineEdit->text(),"Ausflug","Süden",videoFiles,parameters);
}

void MainWindow::showRunning(QString id){
    ui->progressBar->setMaximum(0);
}

void MainWindow::showDone(QString id){
    ui->progressBar->setMaximum(1);
    ui->progressBar->setValue(1);
}

void MainWindow::showError(QString msg){
    QMessageBox msgBox;
    msgBox.setText("There was an Error: "+msg);
    msgBox.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    fileNames = QFileDialog::getOpenFileNames(this, tr("Open AVI"), "/", tr("AVI Files (*.avi)"));
    ui->labelAviFile->setText(fileNames[0]);
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_pushButtonMenu_clicked()
{
    QString menufile = QFileDialog::getOpenFileName(this, tr("Open Menu"), "/", tr("Menu Files (*.menu)"));
    ui->labelMenu->setText(menufile);
    creator->setMenuFile(menufile);
}
