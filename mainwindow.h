/*!
  ** \file mainwindow.h
  ** \date July 2012
  ** \author Andreas Rettig
  ***************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dvdcreator.h"

namespace Ui {
    class MainWindow;
}

/*!
  ** A very simple example implementation of the dvdcreator class
  **
  *******************************************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonChooseAvi_clicked();
    void on_pushButtonChooseMenu_clicked();

    void showRunning(QString id);
    void showDone(QString id);
    void showError(QString msg);


private:
    Ui::MainWindow *ui;
    DVDCreator* creator;
    QStringList fileNames;
};

#endif // MAINWINDOW_H
