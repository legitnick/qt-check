#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFontDialog>
#include <QMainWindow>
#include <QTableView>
#include <QVector>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>
#include <QTextStream>
#include <QTableView>
#include <QAbstractTableModel>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QAbstractItemModel>

#include "tablemodel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public
slots:
    //void about();
    void saveAs();
    void load();
    void newFile();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
void addData(QString line);
private:
    //so, we need: read a file to know which file to  read next
    //2) read that file and a file with all the DMC colors
    //3) display 'em

    void _read(QString path);
    void setupTable(TableModel* itemModel);
    void _display();
    Ui::MainWindow *ui;
    TableModel *itemModel;
};
#endif // MAINWINDOW_H
