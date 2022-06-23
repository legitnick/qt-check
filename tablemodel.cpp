#include "tablemodel.h"
Entrie TableModel::strToEntrie(QString& strEntrie){
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
TableModel::TableModel(QObject *parent,QVector<Entrie>* elems)
    : QAbstractListModel{parent},
      elems( elems)
{

}

void TableModel::_split(QString DMCdata){
    QString curr[5];
    //OK, this killer feature(split) is much better
    QStringList splitData=DMCdata.split("\n");
    for(int i=0;i<splitData.size();i++){

                elems->push_back(strToEntrie(splitData[i]));
    }
}
int TableModel::rowCount(const QModelIndex &parent) const
{
    return elems->count();
}
QVariant TableModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
           return QVariant();

       if (index.row() >= elems->size())
           return QVariant();
       if(role == Qt::DisplayRole){
           int i = index.row();
           int j = index.column();
           const QVariant a = (!j)?(*elems)[i].id:j==1?(*elems)[i].name:(*elems)[i].cl.getString();
           return a;
       }
       return QVariant();
}

/*
void TableModel::_display(){
    //QTableView* tableView=setupTable();
    itemModel = new TableModel();//elems.size()/3-1,3,this
     setupTable(itemModel);
     for(int i = 0;i*3<elems.size()-1;i++){
         for(int j = 0;j<3;j++){
             QModelIndex index = itemModel->index(i,j,QModelIndex());
             const QVariant& a = (!j)?elems[i].id:j==1?elems[i].name:elems[i].cl.getString();
             itemModel->setData(index,a);
         }
}
}
*/
