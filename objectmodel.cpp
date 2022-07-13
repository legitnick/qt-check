#include "objectmodel.h"

ObjectModel::ObjectModel(QObject *parent)
    : QAbstractListModel{parent}
{
}
void ObjectModel::populate(){

    readFile(":txt/dmc_open_data");
    initCheckStates();
}
int ObjectModel::rowCount()const{return m_contacts.length();}
QList<bool> ObjectModel::data()const{
    QList<bool> l;
for(int i = 0;i<m_contacts.length();i++)l[i]=m_contacts.at(i).checked;
}
void ObjectModel::check(int row){
    if (row < 0 || row >= m_contacts.count())
        m_contacts[row].checked^=1;
}

void ObjectModel::append(QString N,QString name,QString color,bool checked){
    m_contacts.append({N,name,color,checked});
}

Contact strToEntrie(QString& strEntrie){
    QStringList strArr = strEntrie.split(',');
    if(strArr.size()<5){return Contact();}
    return {strArr[0],strArr[1],strArr[2],false};
}

void ObjectModel::_split(QString DMCdata){
    QStringList splitData=DMCdata.split("\n");
    for(int i=0;i<splitData.size();i++){

                m_contacts.push_back(strToEntrie(splitData[i]));
    }
}
void ObjectModel::readFile(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(nullptr,"warn","cannot read file!");
            return;
        }

    QTextStream in(&file);
    QString DMCdata = in.readAll();
    _split(DMCdata);//so, we've read the file and now have a vector with entries for a table.
    file.close();
}
void ObjectModel::initCheckStates(){
    QString checkString = state.value("res/check").toString();
    if(checkString.size()<10)return;
    for(int i = 0;i<checkString.size();i++){
        if(checkString[i].toLatin1()-'0')m_contacts[i].checked=true;//toLatin1 is a first function name which does not make too much sense(to me)
    }
}
