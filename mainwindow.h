#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFontDialog>
#include <QMainWindow>
#include <QTableView>
#include <QVector>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QTextStream>
#include <QTableView>
#include <QAbstractTableModel>
#include <QItemDelegate>
#include <QStandardItemModel>

struct Color{
    QString r,g,b; //not really efficient, but this will work easily for sure
    QString getString();
};
struct Entrie{
    Color cl;
    QString name;
    QString id;//thought it would be uint, but there is no consistency apparently
};
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

    /*
    void print();
    void about();
    void paste();
    void cut();
    void copy();
    void open();
    void saveAs();
    void save();

*/
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //so, we need: read a file to know which file to  read next
    //2) read that file and a file with all the DMC colors
    //3) display 'em

    void _read(QString path);
    void setupTable(QStandardItemModel* itemModel);
    void _display();
    void _split(QString DMCdata);
    Entrie strToEntrie(QString& strArr);
    Ui::MainWindow *ui;
    QString currFile;
    QVector<Entrie> elems;
    QStandardItemModel *itemModel;
};
#endif // MAINWINDOW_H
