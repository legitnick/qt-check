#ifndef WIDGETTABLE_H
#define WIDGETTABLE_H

#include <QTableWidget>
#include <QHeaderView>
#include <QTextStream>
#include <QVector>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

struct Color{
    QString r,g,b; //not really efficient, but this will work easily for sure
    QString getString();
};
struct Entrie{
    Color cl;
    QString name;
    int id;//thought it would be uint, but there is no consistency apparently
};
class WidgetTable : public QTableWidget
{
    Q_OBJECT
private slots:
    void doubleClicked(QTableWidgetItem* item);
    void colorize(QTableWidgetItem *item);
    void selected(QTableWidgetItem *item);
private:
    QTableWidgetItem* selectedItem=nullptr;
    QVector<Entrie> elems;
    QVector<bool> checkStates;
    void fillWidgetTable();
    void _read(QString path);
    void _split(QString DMCdata);
    void setupWidgetTable();
    void initCheckStates();
    void _writeFIle();
    Entrie strToEntrie(QString& strArr);
    QSettings state;

public:
    explicit WidgetTable( );
    ~WidgetTable();
};

#endif // WIDGETTABLE_H
