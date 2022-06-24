#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QMessageBox>
#include <QMainWindow>
struct Color{
    QString r,g,b; //not really efficient, but this will work easily for sure
    QString getString();
};
struct Entrie{
    Color cl;
    QString name;
    QString id;//thought it would be uint, but there is no consistency apparently
};

class TableModel : public QAbstractListModel
{
    Q_OBJECT
    Entrie strToEntrie(QString& strEntrie);

    QVector<Entrie>* elems;
public:
    explicit TableModel(QObject *parent = nullptr,QVector<Entrie>*elems=Q_NULLPTR);

    int rowCount(const QModelIndex &parent) const;
    QVariant  data(const QModelIndex &index, int role) const;
public slots:
    void _split(QString DMCdata);
};

#endif // TABLEMODEL_H
