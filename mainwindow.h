#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <bitset>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
using namespace std;
QT_END_NAMESPACE

static string netmasks[] = {"255.255.255.255", "255.255.255.254",
                            "255.255.255.252", "255.255.255.248",
                            "255.255.255.240", "255.255.255.224",
                            "255.255.255.192", "255.255.255.128",
                            "255.255.255.0",   "255.255.254.0",
                            "255.255.252.0",   "255.255.248.0",
                            "255.255.240.0",   "255.255.224.0",
                            "255.255.192.0",   "255.255.128.0",
                            "255.255.0.0",     "255.254.0.0",
                            "255.252.0.0",     "255.248.0.0",
                            "255.240.0.0",     "255.224.0.0",
                            "255.192.0.0",     "255.128.0.0",
                            "255.0.0.0",       "254.0.0.0",
                            "252.0.0.0",       "248.0.0.0",
                            "240.0.0.0",       "224.0.0.0",
                            "192.0.0.0",       "128.0.0.0",
                            "0.0.0.0"};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void prepareNetmask();
    int parseIPv4();
    void computeNetAddress(QString);
    void computeBroadcast(QString);
    void computeFirstAddress(QString);
    void computeLastAddress(QString);
    void computeHostsNumber(QString);
    void binToIpArray(int&);
    void ipArrayToBin(int*, bitset<32>*);
    int splitAddress(QString, int*);
    int iIPv4[4], iNetmask[4];
    bitset<32> *bIPv4, *bNetmask;
private slots:
    void onCompute();
};
#endif // MAINWINDOW_H
