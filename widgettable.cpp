#include "widgettable.h"

WidgetTable::WidgetTable( )
    :QTableWidget()
{


    _read(":resources/resources/_visible_.txt");
    fillWidgetTable();
}

QString Color::getString(){
    return '('+r+','+g+','+b+')';
}
void WidgetTable::selected(QTableWidgetItem* item){
    //resolve two problems: one of changing color only to the left, second of leaving all the changed colors behind.by having
    int i = item->row();
    int cols = this->columnCount()-1;
    if(!selectedItem){

        selectedItem = this->item(i,cols);
        selected(selectedItem);
    }

    if(selectedItem->row()!=i) {
        colorize(selectedItem);//unselect prev
        selectedItem = this->item(i,cols);
        selected(selectedItem);
    }
    uint r = elems[i].cl.r.toUInt();
    uint g = elems[i].cl.g.toUInt();
    uint b = elems[i].cl.b.toUInt();
    uint a = 10;
    if(r+a<255&&g+a<255&&b+a<255){
        r+=a;
        g+=a;
        b+=a;
    }

    QColor color(r,g,b);
    item->setBackground(color);
    if(cols!=item->column()){
        //don't want to change checkbox color
        color = QColor(250,250,250);
        item->setForeground(color);
    }
    if(int j = item->column())selected(this->item(i,j-1));

}
void WidgetTable::colorize(QTableWidgetItem *item){
    int i = item->row();
    uint r = elems[i].cl.r.toUInt();
    uint g = elems[i].cl.g.toUInt();
    uint b = elems[i].cl.b.toUInt();
    QColor color(r,g,b);
    item->setBackground(color);

    color = QColor(2,2,2);
    item->setForeground(color);
    if(int j = item->column())colorize(this->item(i,j-1));
}
void WidgetTable::doubleClicked(QTableWidgetItem* item){
    int i = item->row();
    checkStates[i] = !checkStates[i];//toggle model
    this->item(i,this->columnCount()-1)->setCheckState(checkStates[i]?Qt::Checked:Qt::Unchecked);
}
void WidgetTable::setupWidgetTable(){

    connect(this,&QTableWidget::itemChanged,this,&WidgetTable::colorize);
    connect(this,&QTableWidget::itemPressed,this,&WidgetTable::selected);
    connect(this,&QTableWidget::itemDoubleClicked,this,&WidgetTable::doubleClicked);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->horizontalHeader()->setStretchLastSection(true);
    this->verticalHeader()->hide();
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionMode(QAbstractItemView::NoSelection);
    this->setSortingEnabled(true);

    this->setFocusPolicy(Qt::NoFocus);//will work for now, stylesheet and signal methods didn't


    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     this->setStyleSheet(
                                           "border: 1px solid #000000;"
                //make selected row darker, and text brighter

                                           "QHeaderView::section {"
                                           "border-top: 0px solid 4181C0;"
                                           "border-bottom: 1px solid 4181C0;"
                                           "border-right: 1px solid 4181C0;"
                                           "background:#3A3A2F;"
                                           "color: #4181C0;"

                                           "}"

    /*                                       "background-color: #2F2F2F;"
                                           "color: #4181C0;"

                                   try without stylesheet for debug

    */
                       );

}
void WidgetTable::initCheckStates(){
    QString checkString = state.value("res/check").toString();
    checkStates = QVector<bool>(this->rowCount(),false) ;
    if(checkString.size()<10)return;//the file size is at the very least 151 bytes, so it'll work on the first launch
    for(int i = 0;i<checkString.size();i++){
        if(checkString[i].toLatin1()-'0')checkStates[i]=true;//toLatin1 is a first function name which does not make too much sense(to me)
    }
}
void WidgetTable::fillWidgetTable(){
    setupWidgetTable();
    this->setColumnCount(4);
    this->setRowCount(elems.size()/3);

    QStringList headers = {"N","name","color","presence"};
    this->setHorizontalHeaderLabels(headers);
    initCheckStates();
    for(int i = 0;i<this->rowCount();i++){
        for(int j = 0;j<this->columnCount();j++){

            QTableWidgetItem* item = new QTableWidgetItem();
            if(j!=this->columnCount()-1){
                const QString& a = (!j)?QString::number(elems[i].id):j==1?elems[i].name:elems[i].cl.getString();
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

    disconnect(this,&QTableWidget::itemChanged,this,&WidgetTable::colorize);//I figure changing background probably triggers change sygnal
}

Entrie WidgetTable::strToEntrie(QString& strEntrie){
    QStringList strArr = strEntrie.split(',');
    if(strArr.size()<5){return Entrie();}
    Entrie a;
    a.id = strArr[0].toInt();
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
            QMessageBox::warning(this, "Warning", "Cannot read file: "+ path+ file.errorString());
            return;
        }

    QTextStream in(&file);
    QString DMCdata = in.readAll();
    _split(DMCdata);//so, we've read the file and now have a vector with entries for a table.
    file.close();
}
void WidgetTable::_writeFIle(){
    QString checkString;
    for(int i = 0;i<checkStates.size();i++){
        if(checkStates[i]){checkString+="1";continue;}//no elses, idk why would you do that honestly)
        checkString+="0";
    }
    state.setValue("res/check",checkString);
}
WidgetTable::~WidgetTable(){
    _writeFIle();
}
