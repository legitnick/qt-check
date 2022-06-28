#include "mainwindow.h"

#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table = new WidgetTable();
    setCentralWidget(table);
    if (!QDir::setCurrent(QCoreApplication::applicationDirPath())) {
      // Enters here if assets are not loaded?
        QMessageBox::warning(this,"Initializatoin error","The assets are not loaded correctly");

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
