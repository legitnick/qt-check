#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->actionExit->setShortcut(Qt::Key_Q | Qt::CTRL);
    itemModel = new TableModel();
    this->setupTable();
    connect(this,&MainWindow::addData,itemModel,&TableModel::_split);
    _read("_visible_");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::_read(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }
    QTextStream in(&file);
    QString DMCdata = in.readAll();
    addData(DMCdata);//so, we've read the file and now have a vector with entries for a table.
}
void MainWindow::setupTable(){

    ui->tableView->setModel(itemModel);
            ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableView->horizontalHeader()->setStretchLastSection(true);
            ui->tableView->verticalHeader()->hide();
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableView->setSortingEnabled(true);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

