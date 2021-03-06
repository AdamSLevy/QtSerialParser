#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>

#include "serialportmanager.h"
#include "setcustombaud.h"

#define AS_HEX 0
#define AS_CHAR 1
#define AS_BIT 2

#define SEND_DEFAULT AS_HEX
#define OUT_DEFAULT AS_HEX

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void updatePortSettings(PortSettings);
    void reconnect();
    void send(QByteArray);

private slots:
    void handlePacket(QByteArray);
    void handleSerialPortError(QSerialPort::SerialPortError);
    void handleSerialNotFound();
    void handleConnected();
    void handleFailedToConnect();
    void handleSendMessageFormatting();
    void changeDisplayFormat(bool asChar);

    void enableClearButton();

    void handlePortSettingsChanged(PortSettings);
    void handleSent(qint64 numBytes);

    void populatePortMenu();

    void on_sendMessage_clicked();

    void changePort();
    void changeBaud();
    void changeDataBits(QAction * action);
    void changeFlowControl(QAction * action);
    void changeStopBits(QAction * action);
    void changeParity(QAction * action);
    void customBaud(int baud);

    void on_actionReconnect_triggered();

    void on_actionCustom_baud_triggered();

    void on_clear_clicked();

    void on_clearDisplayButton_clicked();

private:
    Ui::MainWindow *ui;

    SerialPortManager *m_comPort;
    QThread * m_portThread;

    PortSettings m_portSettings;
    bool m_connected;
    int m_numBytesDisplayed;
    QString m_textAsHex;
    QString m_text;

    void statusMessage( QString );
    void statusMessage(QString message, int timeout);
};

#endif // MAINWINDOW_H
