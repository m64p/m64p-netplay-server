#ifndef UDPSERVER_H
#define UDPSERVER_H
#include <QObject>
#include <QUdpSocket>
#include <QCache>

class InputState : public QObject
{
    Q_OBJECT
public:
    QPair<uint32_t, uint8_t> data; //<BUTTONS, Plugin>
};

class UdpServer : public QObject
{
    Q_OBJECT
public:
    UdpServer(int _port);
    ~UdpServer();
    void readPendingDatagrams();
    int getPort();
protected:
    void timerEvent(QTimerEvent *te) Q_DECL_OVERRIDE;
signals:
    void killMe(int port);
private:
    void sendInput(uint32_t count, QHostAddress address, int port, uint8_t playerNum, uint8_t spectator);
    void checkIfExists(uint8_t playerNumber, uint32_t count);
    void sendRegResponse(uint8_t playerNumber, uint32_t reg_id, QHostAddress address, int port);
    QUdpSocket* udpSocket;
    QCache<uint32_t, InputState> inputs[4]; //<count, <BUTTONS, Plugin>>
    QHash<uint8_t, uint32_t> reg; //player number, reg_id
    QList<QPair<uint32_t, uint8_t>> buttons[4];
    uint32_t lead_count[4];
    uint8_t buffer_size[4];
    int buffer_health[4];
    int timerId;
    int port;
    uint32_t keepalive;
};

#endif