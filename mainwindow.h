#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDockWidget>
#include <QDirIterator>
#include <QDir>
#include <QListView>
#include <QMessageBox>
#include <QListWidgetItem>
#include "../../pluginGUI/widget.h"
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

const double M_PI = 3.14;

typedef unsigned __int16 WORD;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void filter(char * image, int width, int height);
    void startApp();
    void startAppOnePlugin();
    void checkLicense();
    void getResponse();
    void getKey();
    void setImage(QByteArray image);
    ~MainWindow();

private slots:
    void on_bw_clicked();

    void on_filterList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    QString file;
    QString keyFileName;
    QPixmap pixmap;
    QByteArray original;
    QList<QDockWidget*> docks;
    QNetworkReply *tt;
    QString userInfoStr;
    QList<PluginGUI*> pluginList;
    QMessageBox box;
    QByteArray msgForVIPUsers;
};
#endif // MAINWINDOW_H
