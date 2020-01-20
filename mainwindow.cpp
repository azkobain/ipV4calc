#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    prepareNetmask();
    bIPv4 = new bitset<32>(0);
    bNetmask = new bitset<32>(0);
    connect(ui->pbCompute, SIGNAL(released()), this, SLOT(onCompute()));
}

MainWindow::~MainWindow() {
    delete ui;
}

int MainWindow::splitAddress(QString source, int *arr) {
    QStringList lsIPv4 = source.split(".");
    int i = 0;

    for (auto oct : lsIPv4) {
        *(arr + i) = oct.toInt();
        if (*(arr + i) >= 0 && *(arr + i) <= 255)
            ++i;
        else
            return 1;
    }
    return 0;
}

void MainWindow::prepareNetmask() {
    for (int i = 0; i < 33; i++)
        ui->cbNetmask->addItem(QString("/") + QString::number(32 - i) +
                               QString(" - ") + QString::fromStdString(netmasks[i]));
}

void MainWindow::binToIpArray(int &) {

}

#include <QDebug>
void MainWindow::ipArrayToBin(int *arr, bitset<32> *bOut) {
    for (int i = 0; i < 4; i++) {
        bitset<32> tmp = *(arr + i);
        *bOut |= tmp;
        if (i == 3)
            break;
        *bOut <<= 8;
    }
}

void MainWindow::computeNetAddress(QString output) {
    int netAddr[4];
    bitset<32> tmp = *bIPv4 & *bNetmask, mask = 255;
    netAddr[3] = (tmp & mask).to_ulong();
    tmp >>= 8;
    netAddr[2] = (tmp & mask).to_ulong();
    tmp >>= 8;
    netAddr[1] = (tmp & mask).to_ulong();
    tmp >>= 8;
    netAddr[0] = (tmp & mask).to_ulong();
    ui->teResults->append(output);
    QString qsNetAddress = QString::number(netAddr[0]) + QString(".") +
                           QString::number(netAddr[1]) + QString(".") +
                           QString::number(netAddr[2]) + QString(".") +
                           QString::number(netAddr[3]) + QString("\n");
    ui->teResults->append(qsNetAddress);
}

void MainWindow::computeBroadcast(QString output) {
    int netAddr[4];
    bitset<32> tmp = *bIPv4 | ~(*bNetmask), mask = 255;
    netAddr[3] = (tmp & mask).to_ulong();
    tmp >>= 8;
    netAddr[2] = (tmp & mask).to_ulong();
    tmp >>= 8;
    netAddr[1] = (tmp & mask).to_ulong();
    tmp >>= 8;
    netAddr[0] = (tmp & mask).to_ulong();
    ui->teResults->append(output);
    QString qsBroadcast = QString::number(netAddr[0]) + QString(".") +
                           QString::number(netAddr[1]) + QString(".") +
                           QString::number(netAddr[2]) + QString(".") +
                           QString::number(netAddr[3]);
    ui->teResults->append(qsBroadcast);
}

void MainWindow::computeFirstAddress(QString output) {
    ui->teResults->append(output);
}

void MainWindow::computeLastAddress(QString output) {
    ui->teResults->append(output);
}

void MainWindow::computeHostsNumber(QString output) {
    ui->teResults->append(output);
}

void MainWindow::onCompute() {
    ui->teResults->clear();
    if (splitAddress(ui->leIPv4->text(), iIPv4) != 0)
        ui->teResults->append("Wrong IPv4 format. Re-enter IPv4 address");
    splitAddress(QString::fromStdString(netmasks[ui->cbNetmask->currentIndex()]), iNetmask);

    ipArrayToBin(iIPv4, bIPv4);
    ipArrayToBin(iNetmask, bNetmask);
    computeNetAddress(QString("IP network address: "));
    computeBroadcast(QString("Broadcast address: "));
    ui->teResults->setReadOnly(true);
}
