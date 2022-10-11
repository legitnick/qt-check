#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include <QtQml/qqmlregistration.h>
#include <QAbstractListModel>
#include <QSettings>
#include <QTextStream>
#include <QVector>

#include <QFile>
#include <QMessageBox>

struct Contact {
    QString N;
    QString name;
    QString m_color;
    bool checked;
    Contact(QString N, QString name, QString m_color, bool checked){
        this->N = N;
        this->name =name;
        this->m_color = m_color;
        this->checked = checked;
    }
    Contact(){}
};
class ObjectModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit ObjectModel(QObject *parent = nullptr);
    ~ObjectModel();
    void append(QString N,QString name,QString color,bool checked);
    QVariant data(const QModelIndex& index, int role)const;
    int rowCount(const QModelIndex& index)const;
    Q_INVOKABLE void check(int row);
    Q_INVOKABLE Qt::CheckState getCheck(int row);
    Q_INVOKABLE QVariant getColor(int row);
    Q_INVOKABLE QString getN(int row);
    Q_INVOKABLE  QString getName(int row);
    void populate();


private:
    void writeState();
    void readFile(QString file);
    void initCheckStates();
    void _split(QString DMCdata);
    QSettings state;
    QList<Contact*> m_contacts;
};

#endif // OBJECTMODEL_H
