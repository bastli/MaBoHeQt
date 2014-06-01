#include "MaBoHeMain.hpp"
#include "ui_MaBoHeMain.h"

///////////////////////////////////////////////////////////////////////////////
MaBoHeMain::MaBoHeMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MaBoHeMain)
{
    ui->setupUi(this);

    connect(ui->scanButton, SIGNAL(clicked()), this, SLOT(scanForDevices()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectButton()));

    connect(&heater, SIGNAL(heater_connected(QSerialPort)), this, SLOT(heater_connected(QSerialPort)));
    connect(&heater, SIGNAL(heater_disconnected()), this, SLOT(heater_disconnected()));
    connect(&heater, SIGNAL(serial_error(QString,QString)), this, SLOT(serial_error(QString,QString)));

    scanForDevices();
    heater_disconnected();

    ui->graph->addGraph();

    QVector<double> x(250), y(250);

    for (int i = 0; i < 250; ++i) {
        x[i] = i;
        y[i] = exp(-i/150.0)*cos(i/10.0);
    }
    ui->graph->graph(0)->setData(x, y);
    ui->graph->graph(0)->rescaleAxes();
    ui->graph->xAxis->setLabel("time in seconds");
    ui->graph->yAxis->setLabel("temperature [C]");
    ui->graph->xAxis->setRange(-1,2);
}
///////////////////////////////////////////////////////////////////////////////
MaBoHeMain::~MaBoHeMain()
{
    delete ui;
}
///////////////////////////////////////////////////////////////////////////////
void MaBoHeMain::scanForDevices()
{
    QList<QSerialPortInfo> devices = QSerialPortInfo::availablePorts();

    ui->deviceChooser->clear();

    foreach(QSerialPortInfo d, devices) {
        ui->deviceChooser->addItem(d.portName(), QVariant::fromValue(d));
    }
}
///////////////////////////////////////////////////////////////////////////////
void MaBoHeMain::connectButton()
{
    if (!heater.isConnected()) {
        qDebug() << "trying to connect";

        QSerialPortInfo port = ui->deviceChooser->currentData().value<QSerialPortInfo>();
        connectHeater(port);
    } else {
        qDebug() << "trying to disconnect";

        heater.serialDisconnect();
    }
}
///////////////////////////////////////////////////////////////////////////////
void MaBoHeMain::connectHeater(const QSerialPortInfo &port)
{
    if (port.isValid()) {
        heater.serialConnect(port);
    } else {
        QMessageBox::critical(this, tr("Cannot connect"), tr("Invalid serial port selected."));
    }
}
///////////////////////////////////////////////////////////////////////////////
void MaBoHeMain::heater_connected(const QSerialPort& port)
{
    ui->statusBar->showMessage(tr("connected to %1").arg(port.portName()));
    ui->connectButton->setText(tr("disconnect"));

    ui->mainGuiLayout->setEnabled(true);
}
///////////////////////////////////////////////////////////////////////////////
void MaBoHeMain::heater_disconnected()
{
    ui->statusBar->showMessage(tr("disconnected"));
    ui->connectButton->setText(tr("connect"));

    ui->mainGuiLayout->setEnabled(false);
}
///////////////////////////////////////////////////////////////////////////////
void MaBoHeMain::serial_error(const QString& category, const QString& message)
{
    QMessageBox::critical(this, tr("Error during %1").arg(category), message);
}
///////////////////////////////////////////////////////////////////////////////
