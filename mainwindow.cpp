#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QList>
#include <QAction>
#include <QActionGroup>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "$APPIMAGE:" << qgetenv("APPIMAGE");
    QProcess process;
    process.start("which AppImageUpdate");
    process.waitForFinished(500);
    QString appImageUpdatePath = process.readAllStandardOutput();

    /* Enable the 'Update' menu only if AppImageUpdate is on the $PATH
     * and the $APPIMAGE environvent variable is set */
    qDebug() << "which AppImageUpdate:" << appImageUpdatePath;
    if((appImageUpdatePath != "") && (qgetenv("APPIMAGE") != NULL)) {
        qDebug() << "Enable 'Update' menu";
        QList<QMenu*> lst;
        lst = ui->menuBar->findChildren<QMenu*>();
        lst[1]->actions()[0]->setEnabled(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionUpdate_triggered()
{
    QProcess process;
    process.start("AppImageUpdate", QStringList() << qgetenv("APPIMAGE"));
    process.waitForFinished(-1);
}

void MainWindow::on_actionAbout_AppImageUpdateExample_triggered()
{
    QMessageBox::about(this, trUtf8("QtAppImageUpdateExample"), trUtf8("An example that shows\nhow to call AppImageUpdate\nfrom a Qt application"));
}
