#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    file = "F:/lena512.bmp";
    pixmap.load(file);

    QDir dir("plugins");

    QStringList subdirs = dir.entryList();

    for(auto subdir : subdirs)
    {
        QFile pluginDescription("plugins/" + subdir + "/pluginDescription.xml");

        if(!pluginDescription.open(QIODevice::ReadOnly)) continue;

        PluginGUI * test = new PluginGUI("plugins/" + subdir + "/" + subdir + ".dll");

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
        if(data.split(";")[1] == userInfoStr.split(";")[1]) {
            QString url = "http://91.239.27.88/users/" + userInfoStr.split(";")[0] + "/key";

            tt =manager->get(QNetworkRequest(QUrl(url)));

            connect(tt, &QIODevice::readyRead, this, &MainWindow::getKey);
        }
    }

    int a = 5;
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

void MainWindow::on_bw_clicked()
{
    int kernelSize = 5;
    double ** GKernel;
    int imgWidth, imgHeight;
    int mode = 0;

    //Выделение памяти для хранения ядра
    GKernel = new double *[kernelSize];
    for (int i = 0; i < kernelSize; i++)
        GKernel[i] = new double[kernelSize];

    QFile image(file);
    image.open(QIODevice::ReadOnly);
    //Чтение заголовка файла
    QByteArray data = image.read(sizeof(BMPheader));


    BMPheader * header = (BMPheader *)data.data();

    //Сохранение значений ширины и высоты записаных в заголовке
    imgWidth = header->biWidth;
    imgHeight = header->biHeight;
    original = image.read(header->biSizeImage);

    QFile resImageFile("F:/result.bmp");
    resImageFile.open(QIODevice::WriteOnly);

    //Копирования точно такого же заголовка в результирующий файл
    resImageFile.write((char*)header, sizeof(BMPheader));

    int bytesCount = imgWidth * imgHeight * header->biBitCount / 8;

    char * padding = new char[header->bfOffBits - sizeof(BMPheader)];
    image.read(padding, header->bfOffBits - sizeof(BMPheader));
    resImageFile.write(padding, header->bfOffBits - sizeof(BMPheader));

    image.close();

    filter(original.data(), imgWidth, imgHeight);

    resImageFile.write((char *)original.data(), header->biSizeImage);
    resImageFile.close();
}

void MainWindow::on_filterList_itemDoubleClicked(QListWidgetItem *item)
{
//    this->addDockWidget(Qt::BottomDockWidgetArea, docks[ui->filterList->currentRow()]);

////    if (!docks[ui->filterList->currentRow()]->) {

////    }
}
