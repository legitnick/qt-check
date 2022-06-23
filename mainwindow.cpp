#include "mainwindow.h"

#include "ui_mainwindow.h"
QString Color::getString(){
    return '('+r+','+g+','+b+')';
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->actionExit->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::load);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveAs);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    itemModel = new TableModel();
    connect(this,&MainWindow::addData,itemModel,&TableModel::_split);
    _read("_visible_");
    _display();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile(){
    //set an app to its initial state
}
void MainWindow::load(){
    QString fileName = QFileDialog::getOpenFileName(this,"Open");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }


    QTextStream in(&file);
    QString txt = in.readAll();



    //change the state of the current app accordingly to info saved here
}
void MainWindow::saveAs(){

    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    //save current app state to the file (which would be something like 1,0 to text files meaning checked state on the checkboxes)

    file.close();
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
void MainWindow::setupTable(TableModel* itemModel){

    ui->tableView->setModel(itemModel);
            ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableView->horizontalHeader()->setStretchLastSection(true);
            ui->tableView->verticalHeader()->hide();
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableView->setSortingEnabled(true);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

