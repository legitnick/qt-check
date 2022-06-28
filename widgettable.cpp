#include "widgettable.h"

WidgetTable::WidgetTable( )
    :QTableWidget()
{

    _read("_visible_");
    fillWidgetTable();
}

QString Color::getString(){
    return '('+r+','+g+','+b+')';
}
void WidgetTable::colorize(QTableWidgetItem *item){
    int i = item->row();
    uint r = elems[i].cl.r.toUInt();
    uint g = elems[i].cl.g.toUInt();
    uint b = elems[i].cl.b.toUInt();
    QColor color(r,g,b);
    item->setBackground(color);
    if(int j = item->column())colorize(this->item(i,j-1));//recursion to colorize row
}
void WidgetTable::doubleClicked(QTableWidgetItem* item){
    int i = item->row();
    checkStates[i] = !checkStates[i];//toggle model
    this->item(i,this->columnCount()-1)->setCheckState(checkStates[i]?Qt::Checked:Qt::Unchecked);

    //this line does not work as this->itemAt(i,3) is not found...
    //will try recursion once again

    //this->itemAt(i,3)->setCheckState(checkStates[i]?Qt::Checked:Qt::Unchecked);//set according view
}
void WidgetTable::setupWidgetTable(){
    connect(this,&QTableWidget::itemChanged,this,&WidgetTable::colorize);
    connect(this,&QTableWidget::itemDoubleClicked,this,&WidgetTable::doubleClicked);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->horizontalHeader()->setStretchLastSection(true);
    this->verticalHeader()->hide();
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSortingEnabled(true);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     this->setStyleSheet(
                                           "border: 1px solid #000000;"
                                           "QHeaderView::section {"
                                           "border-top: 0px solid 4181C0;"
                                           "border-bottom: 1px solid 4181C0;"
                                           "border-right: 1px solid 4181C0;"
                                           "background:#3A3A2F;"
                                           "color: #4181C0;"
                                           "}"

    /*                                       "background-color: #2F2F2F;"
                                           "color: #4181C0;"
                                           "selection-background-color: #4181C0;"
                                           "selection-color: #FFF;"
                                   try without stylesheet for debug

    */
                       );

}
void WidgetTable::initCheckStates(){
    QFile file("check");
    checkStates = QVector<bool>(this->rowCount(),false) ;
    if(file.size()<128)return;//the file size is at the very least 151 bytes, so it'll work on the first launch
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: check "+ file.errorString());
            return;
        }

    QTextStream in(&file);
    QString checkString = in.readAll();
    for(int i = 0;i<checkString.size();i++){
        if(checkString[i].toLatin1()-'0')checkStates[i]=true;//toLatin1 is a first function name which does not make too much sense(to me)
    }
    file.close();
}
void WidgetTable::fillWidgetTable(){
    setupWidgetTable();
    this->setColumnCount(4);
    this->setRowCount(elems.size()/3);

    initCheckStates();
    for(int i = 0;i<this->rowCount();i++){
        for(int j = 0;j<this->columnCount();j++){

            QTableWidgetItem* item = new QTableWidgetItem();
            if(j!=this->columnCount()-1){
                const QString& a = (!j)?elems[i].id:j==1?elems[i].name:elems[i].cl.getString();
                item->setText(a);
            }else{
                auto currFlags = item->flags();
                item->setFlags(currFlags&(~Qt::ItemIsUserCheckable));//so hopefully this means users cannot check by checkbox anymore
                item->setCheckState(checkStates[i]?Qt::Checked:Qt::Unchecked);
            }

            item->setTextAlignment(Qt::AlignHCenter);
            this->setItem(i,j,item);

        }
    }
}

Entrie WidgetTable::strToEntrie(QString& strEntrie){
    QStringList strArr = strEntrie.split(',');
    if(strArr.size()<5){return Entrie();}
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
void WidgetTable::_split(QString DMCdata){
    QStringList splitData=DMCdata.split("\n");
    for(int i=0;i<splitData.size();i++){

                elems.push_back(strToEntrie(splitData[i]));
    }
}
void WidgetTable::_read(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: "+ path+ file.errorString());
            return;
        }

    QTextStream in(&file);
    QString DMCdata = in.readAll();
    _split(DMCdata);//so, we've read the file and now have a vector with entries for a table.
    file.close();
}
void WidgetTable::_writeFIle(){
    QFile file("check");
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: check"+ file.errorString());
            return;
        }
    file.resize(0);
    QTextStream out(&file);
    for(bool el:checkStates)
        out<<(int)el;
    file.close();
}
WidgetTable::~WidgetTable(){
    _writeFIle();
}
