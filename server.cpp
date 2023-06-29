#include "server.h"
#include "ui_server.h"
#include"globals.h"
Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{

    ui->setupUi(this);

    m_server = new QTcpServer();

    if(m_server->listen(QHostAddress::Any, 8080))
    {
       connect(m_server, &QTcpServer::newConnection, this, &Server::newConnection);
       //gif listening
    }
    else
    {
        QMessageBox::critical(this,"QTCPServer",QString("Unable to start the server: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
        //design
    }
}


void Server::newConnection()
{
    while (m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());
}

void Server::appendToSocketList(QTcpSocket* socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &Server::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &Server::displayError);

}

void Server::readSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;
       if(socket->isOpen())
       {

           foreach (QTcpSocket* sockett,connection_set)
              {
                  if(sockett->socketDescriptor() != socket->socketDescriptor())
                  {
                        QDataStream socketStream(sockett);
                        socketStream.setVersion(QDataStream::Qt_5_15);
                        socketStream << buffer;
                        break;
                  }
            }

    }
}
void Server::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QSet<QTcpSocket*>::iterator it = connection_set.find(socket);
    if (it != connection_set.end()){
        //displayMessage(QString("INFO :: A client has just left the room").arg(socket->socketDescriptor()));
        //wait for 60 sec
        connection_set.remove(*it);
    }

    socket->deleteLater();
}

void Server::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
        break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "QTCPServer", "The host was not found. Please check the host name and port settings.");
        break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "QTCPServer", "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;
        default:
            QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
            QMessageBox::information(this, "QTCPServer", QString("The following error occurred: %1.").arg(socket->errorString()));
        break;
    }
}

//void Server::clientConnected(){

//}

Server::~Server()
{
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    m_server->deleteLater();
    delete ui;
}
