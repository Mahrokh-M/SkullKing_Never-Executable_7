#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>
namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

signals:
    void newMessage(QString);
    //void hide_items();
private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);
    //void clientConnected();
   // void sendMessage(QTcpSocket* socket);


private:
    Ui::Server *ui;

    QTcpServer* m_server;
    QSet<QTcpSocket*> connection_set;

};

#endif // SERVER_H
