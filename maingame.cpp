#include "maingame.h"
#include "ui_maingame.h"

mainGame::mainGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainGame)
{
    ui->setupUi(this);
    //show loading gif
    socket = new QTcpSocket(this);

    connect(this, &mainGame::newMessage, this, &mainGame::displayMessage);
    connect(socket, &QTcpSocket::readyRead, this, &mainGame::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &mainGame::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &mainGame::displayError);

    //socket->connectToHost("server_ip",8080);
    socket->connectToHost("192.168.43.216",8080);
    // based on server ip
    if(socket->waitForConnected()){
     //hide loading gif
    }
    else{
        //design
        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        exit(EXIT_FAILURE);
    }
}

mainGame::~mainGame()
{
    if(socket->isOpen())
        socket->close();
    delete ui;
}

void mainGame::readSocket()
{
    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);

     if(fileType=="message"){
        QString message = QString("%1").arg(QString::fromStdString(buffer.toStdString()));
        emit newMessage(message);
    }
}

void mainGame::discardSocket()
{

    //Trying to connect to server and wait for 60 sec if not:
    socket->deleteLater();
    socket=nullptr;
    //You lost message

}

void mainGame::displayError(QAbstractSocket::SocketError socketError)
{
    //design
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
        break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "QTCPClient", "The host was not found. Please check the host name and port settings.");
        break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "QTCPClient", "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;
        default:
            QMessageBox::information(this, "QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        break;
    }
}


void mainGame::displayMessage(const QString& str)
{
    //set label and compare
}
