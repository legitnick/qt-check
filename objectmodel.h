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
    QString color;
    bool checked;
};
class ObjectModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit ObjectModel(QObject *parent = nullptr);
    void append(QString N,QString name,QString color,bool checked);
    virtual int rowCount() const final;
    virtual QList<bool> data()const final;
    Q_INVOKABLE void check(int row);
    void populate();


private:

    void readFile(QString file);
    void initCheckStates();
    void _split(QString DMCdata);
    QSettings state;
    QList<Contact> m_contacts;
};

#endif // OBJECTMODEL_H
