#include "objectmodel.h"
ObjectModel::~ObjectModel(){
    writeState();
}
ObjectModel::ObjectModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_contacts = QList<Contact*> (100);
    readFile(":txt/dmc_open_data");
    initCheckStates();
}

QVariant ObjectModel::getColor(int row){

    if (row < 0 || row >= m_contacts.count()){
    QList<QString> a = m_contacts[row]->m_color.split(",");
    return QColor(a[0].toInt(),a[1].toInt(),a[2].toInt());
 }
}
QVariant ObjectModel:: data(const QModelIndex& index, int role = Qt::DisplayRole)const{}
int ObjectModel::rowCount(const QModelIndex& index)const{return m_contacts.length();}
QString ObjectModel::getN(int row){

    if (row < 0 || row >= m_contacts.count())
        return m_contacts[row]->N;
    return "NOTREACHED";
}
Qt::CheckState ObjectModel::getCheck(int row){

    if (row < 0 || row >= m_contacts.count())
    return (m_contacts[row]->checked)?Qt::Checked
                                   :Qt::Unchecked;
    return Qt::Unchecked;
}
QString ObjectModel::getName(int row){

    if (row < 0 || row >= m_contacts.count())
    return m_contacts[row]->name;
    return "NOTREACHED";
 }
void ObjectModel::check(int row){
    if (row < 0 || row >= m_contacts.count())
        m_contacts[row]->checked^=1;
}


void ObjectModel::append(QString N,QString name,QString color,bool checked){
    m_contacts.append(new Contact(N,name,color,checked));
}

Contact* strToEntrie(QString& strEntrie){
    QStringList strArr = strEntrie.split(',');
    if(strArr.size()<5){return new Contact();}
    return new Contact(strArr[0],strArr[1],strArr[2]+","+strArr[3]+","+strArr[4],false);
}

void ObjectModel::_split(QString DMCdata){
    QStringList splitData=DMCdata.split("\n");
    for(int i=0;i<splitData.size();i++){

                m_contacts.push_back(strToEntrie(splitData[i]));
    }
}
void ObjectModel::writeState(){
    QString checkString;
    for(int i = 0;i<m_contacts.size();i++){
        if(m_contacts[i]->checked)checkString+="1";//no elses, idk why would you do that honestly)
        else checkString+="0";
    }
    state.setValue("res/check",checkString);
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
        if(checkString[i].toLatin1()-'0'){m_contacts[i]->checked=true;} //toLatin1 is a first function name which does not make too much sense(to me)
    }
}
