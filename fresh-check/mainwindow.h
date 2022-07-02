#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "widgettable.h"
#include <QtNetworkAuth>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public
slots:
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WidgetTable* table;
};
#endif // MAINWINDOW_H

