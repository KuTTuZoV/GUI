#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //startApp();

    msgForVIPUsers = "0KHQstGP0LbQuNGC0LXRgdGMINGBINC60L7QvNCw0L3QtNC+0Lkg0YDQsNC30YDQsNCx0L7RgtGH0LjQutC+0LIg0LTQu9GPINC00LDQu9GM0L3QtdC50YjQtdC5INGA0LDQsdC+0YLRiy4g0JzRiyDQstC40LTQuNC8INCyINCS0LDRgSDQsdC+0LvRjNGI0L7QuSDQv9C+0YLQtdC90YbQuNCw0Lsg0LLQt9C70L7QvNGJ0LjQutCwINCf0J4u";

    checkLicense();
    //ui->label->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::filter(char * image, int width, int height)
{
    //char * result = new char[height*width];

    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            //image[i*width + j] = image[i*width + j] * 1;
        }

    //pixmap.loadFromData((const uchar*)image, 174000,"BMP");
    //ui->label->setPixmap(pixmap);
}

void MainWindow::startApp()
{
    QFile original("F:/lena512color.bmp");

    original.open(QIODevice::ReadOnly);

    QByteArray imgData = original.readAll();

    file = "F:/lena512color.bmp";
    pixmap.load(file);

    QDir dir("plugins");

    QStringList subdirs = dir.entryList();

    for(auto subdir : subdirs)
    {
        QFile pluginDescription("plugins/" + subdir + "/pluginDescription.xml");

        if(!pluginDescription.open(QIODevice::ReadOnly)) continue;

        PluginGUI * test = new PluginGUI("plugins/" + subdir + "/" + subdir + ".dll");

        test->setPicture(imgData);
        connect(test, &PluginGUI::filtered, this, &MainWindow::setImage);

        pluginList.append(test);

        test->readXML(pluginDescription.readAll());
        pluginDescription.close();

        QDockWidget * dock = new QDockWidget(test->windowTitle());
        ui->filterList->addItem(test->windowTitle());
        dock->setWidget(test);

        dock->setFeatures(QDockWidget::DockWidgetFloatable |
                         QDockWidget::DockWidgetMovable);
        docks.append(dock);

        this->addDockWidget(Qt::BottomDockWidgetArea, dock);
    }

    this->showMaximized();

    ui->label->setPixmap(pixmap.scaled(1000, 1000, Qt::KeepAspectRatio));
}

void MainWindow::startAppOnePlugin()
{
    QFile original("F:/lena512color.bmp");

    original.open(QIODevice::ReadOnly);

    QByteArray imgData = original.readAll();

    file = "F:/lena512color.bmp";
    pixmap.load(file);

    QDir dir("plugins");

    QStringList subdirs = dir.entryList();

    subdirs.pop_front();
    subdirs.pop_front();

    QFile pluginDescription("plugins/" + subdirs[0] + "/pluginDescription.xml");

    if(!pluginDescription.open(QIODevice::ReadOnly)) return;

    PluginGUI * test = new PluginGUI("plugins/" + subdirs[0] + "/" + subdirs[0] + ".dll");

    test->setPicture(imgData);
    connect(test, &PluginGUI::filtered, this, &MainWindow::setImage);

    pluginList.append(test);

    test->readXML(pluginDescription.readAll());
    pluginDescription.close();

    QDockWidget * dock = new QDockWidget(test->windowTitle());
    ui->filterList->addItem(test->windowTitle());
    dock->setWidget(test);

    dock->setFeatures(QDockWidget::DockWidgetFloatable |
                     QDockWidget::DockWidgetMovable);
    docks.append(dock);

    this->addDockWidget(Qt::BottomDockWidgetArea, dock);

    ui->label->setPixmap(pixmap.scaled(1000, 1000, Qt::KeepAspectRatio));
}

void MainWindow::checkLicense()
{
    //Проверка ключа
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QFile userInfo;
    QString fileTemplate = "%diskName%:/userInfo";
    QString fileName;

    for(int i = 'A'; i < 'Z'; i++) {
        fileName = fileTemplate;
        userInfo.setFileName(fileName.replace("%diskName%", QChar(i)));

        if(!userInfo.open(QIODevice::ReadOnly)) {
            continue;
        }
        else {
            keyFileName = QChar(i) + QString(":/key");

            userInfoStr = userInfo.readAll();

            userInfoStr = QByteArray::fromBase64(userInfoStr.toUtf8());

            QString url = "http://91.239.27.88/users/" + userInfoStr.split(";")[0] + "/userInfo";

            tt =manager->get(QNetworkRequest(QUrl(url)));

            connect(tt, &QIODevice::readyRead, this, &MainWindow::getResponse);
        }
    }
}



void MainWindow::getResponse()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QString data = QByteArray::fromBase64(tt->readAll());

    if(data.split(";")[0] == userInfoStr.split(";")[0]) {
        QString url = "http://91.239.27.88/users/" + userInfoStr.split(";")[0] + "/key";

        QDate date;

        date = QDate::fromString(data.split(';')[1], "dd.MM.yyyy");

        if(data.split(';')[1] != userInfoStr.split(";")[1]) {
            box.setText(QByteArray::fromBase64(msgForVIPUsers));
            box.showNormal();
            return;
        }

        if(QDate::currentDate().daysTo(date) > 0) {

            tt =manager->get(QNetworkRequest(QUrl(url)));

            connect(tt, &QIODevice::readyRead, this, &MainWindow::getKey);
        }
        else {
            box.setText("Истек срок лицензии");
            box.showNormal();
            startAppOnePlugin();
            return;
        }
    }
}

void MainWindow::getKey()
{
    QString data = tt->readAll();

    QFile keyFile(keyFileName);

    if(!keyFile.open(QIODevice::ReadOnly)) {
        return;
    }

    QString key = keyFile.readAll();

    if(data == key) startApp();
}

void MainWindow::setImage(QByteArray image)
{
    pixmap.loadFromData(image);
    ui->label->setPixmap(pixmap.scaled(1000, 1000, Qt::KeepAspectRatio));

    for(auto temp : pluginList) {
        temp->setPicture(image);
    }
}

void MainWindow::on_bw_clicked()
{

}

void MainWindow::on_filterList_itemDoubleClicked(QListWidgetItem *item)
{
//    this->addDockWidget(Qt::BottomDockWidgetArea, docks[ui->filterList->currentRow()]);

////    if (!docks[ui->filterList->currentRow()]->) {

////    }
}
