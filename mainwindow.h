#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dvdcreator.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void showRunning(QString id);
    void showDone(QString id);
    void showError(QString msg);

    void on_pushButtonMenu_clicked();

private:
    Ui::MainWindow *ui;
    DVDCreator* creator;
    QStringList fileNames;
};

#endif // MAINWINDOW_H
