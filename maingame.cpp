#include "maingame.h"
#include "ui_maingame.h"
#include"QMovie"
#include <QHostAddress>
#include <QHostInfo>
#include"globals.h"
mainGame::mainGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainGame)
{
    //show loading gif
    ui->setupUi(this);
    QMovie *gifMovie = new QMovie(":/new/prefix1/Loading.gif");
    ui->label_Loading->setScaledContents(true);
    ui->label_Loading->setMovie(gifMovie);
    gifMovie->start();
    if(server_or_client==1){
        QString IP;
          foreach(const QHostAddress &address, QHostInfo::fromName(QHostInfo::localHostName()).addresses()) {
              if(address.protocol() == QAbstractSocket::IPv4Protocol) {
                  IP = address.toString();
                  break;
              }
          }

     QString server_IP=IP;
      ui->lineEdit_enter_IP->hide();
      ui->IP_show->setText(server_IP);
      ui->OK->hide();
    }
    else if(server_or_client==2){
       //ui->IP->show();
       ui->IP_show->hide();
   }
    socket = new QTcpSocket(this);
    connect(this, &mainGame::newMessage, this, &mainGame::displayMessage);
    connect(socket, &QTcpSocket::readyRead, this, &mainGame::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &mainGame::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &mainGame::displayError);

    //socket->connectToHost("server_ip",8080);
    if(server_or_client==1){
    socket->connectToHost("127.0.0.1",8080);}

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

void mainGame::on_OK_clicked()
{
  socket->connectToHost(ui->lineEdit_enter_IP->text(),8080);
}

