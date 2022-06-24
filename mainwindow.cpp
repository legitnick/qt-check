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

    _read("_visible_");
    _display();
    fillWidgetTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupWidgetTable(){
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::fillWidgetTable(){
    setupWidgetTable();
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(elems.size()/3);
    for(int i = 0;i<ui->tableWidget->rowCount();i++){
        for(int j = 0;j<ui->tableWidget->columnCount();j++){
            if(j!=ui->tableWidget->columnCount()-1){
                const QString& a = (!j)?elems[i].id:j==1?elems[i].name:elems[i].cl.getString();
                QTableWidgetItem* item = new QTableWidgetItem(a);

                ui->tableWidget->setItem(i,j,item);
            }else{
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setCheckState(Qt::Checked);
                ui->tableWidget->setItem(i,j,item);
            }
        }
    }
}
void MainWindow::newFile(){
    currFile = "new Document";
    //set an app to its initial state
}
void MainWindow::load(){
    QString fileName = QFileDialog::getOpenFileName(this,"Open");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }


    currFile = fileName;
    setWindowTitle(currFile);
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
Entrie MainWindow::strToEntrie(QString& strEntrie){
    QStringList strArr = strEntrie.split(',');
    if(strArr.size()<5){QMessageBox::warning(this,"Warning",strEntrie);return Entrie();}
    Entrie a;
    a.id = strArr[0];
    a.name = strArr[1];
    Color cl;
    cl.r = strArr[2];
    cl.g = strArr[3];
    cl.b = strArr[4];
    a.cl = cl;

    return a;
}
void MainWindow::_split(QString DMCdata){
    QString curr[5];
    //OK, this killer feature(split) is much better
    QStringList splitData=DMCdata.split("\n");
    for(int i=0;i<splitData.size();i++){

                elems.push_back(strToEntrie(splitData[i]));
    }
}
void MainWindow::_read(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }
    QTextStream in(&file);
    QString DMCdata = in.readAll();
    _split(DMCdata);//so, we've read the file and now have a vector with entries for a table.
}
void MainWindow::setupTable(QStandardItemModel* itemModel){

            ui->tableView->setModel(itemModel);
            ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableView->horizontalHeader()->setStretchLastSection(true);
            ui->tableView->verticalHeader()->hide();
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableView->setSortingEnabled(true);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::_display(){
    //QTableView* tableView=setupTable();
    itemModel = new QStandardItemModel(elems.size()/3-1,3,this);
     setupTable(itemModel);
     for(int i = 0;i*3<elems.size()-1;i++){
         for(int j = 0;j<3;j++){
             QModelIndex index = itemModel->index(i,j,QModelIndex());
             const QVariant& a = (!j)?elems[i].id:j==1?elems[i].name:elems[i].cl.getString();
             itemModel->setData(index,a);
         }
}
}
