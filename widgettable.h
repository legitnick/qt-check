#ifndef WIDGETTABLE_H
#define WIDGETTABLE_H

#include <QTableWidget>
#include <QHeaderView>
#include <QTextStream>
#include <QVector>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
struct Color{
    QString r,g,b; //not really efficient, but this will work easily for sure
    QString getString();
};
struct Entrie{
    Color cl;
    QString name;
    QString id;//thought it would be uint, but there is no consistency apparently
};
class WidgetTable : public QTableWidget
{
    Q_OBJECT

    QVector<Entrie> elems;
    QVector<bool> checkStates;
    void fillWidgetTable();
    void _read(QString path);
    void _split(QString DMCdata);
    void setupWidgetTable();
    void initCheckStates();

    Entrie strToEntrie(QString& strArr);
private slots:
    void colorize(QTableWidgetItem *item);
public:
    explicit WidgetTable( );
};

#endif // WIDGETTABLE_H
