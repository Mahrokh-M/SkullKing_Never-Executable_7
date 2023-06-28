#include "maingame.h"
#include "ui_maingame.h"
#include"QMovie"
#include <QHostAddress>
#include <QHostInfo>
#include"globals.h"
#include "card.h"
#include <time.h>
//#include <cstdlib>

Card all_cards[42]; //An array of all cards we have in the game
QString all_paths[42];
void initializing_paths();
void who_start();
mainGame::mainGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainGame)
{
    ui->setupUi(this);
    srand(time(NULL));
    initializing_paths();
    for (int i = 0; i < 8; i++) {
        all_cards[i].get_type() = "treasure";
        all_cards[i].get_number() = i + 1;
        all_cards[i].get_value() = i + 1;
    }
    for (int i = 8, j = 0; i < 16; i++, j++) {
        all_cards[i].get_type() = "map";
        all_cards[i].get_number() = j + 1;
        all_cards[i].get_value() = j + 1;
    }
    for (int i = 16, j = 0; i < 24; i++, j++) {
        all_cards[i].get_type() = "parrot";
        all_cards[i].get_number() = j + 1;
        all_cards[i].get_value() = j + 1;
    }
    for (int i = 24, j = 0; i < 32; i++, j++) {
        all_cards[i].get_type() = "flag";
        all_cards[i].get_number() = j + 1;
        all_cards[i].get_value() = j + 11;
    }

    for (int i = 32; i < 36; i++) {
        all_cards[i].get_type() = "pirate";
        all_cards[i].get_number() = 0;
        all_cards[i].get_value() = 20;
    }
    for (int i = 36; i < 39; i++) {
        all_cards[i].get_type() = "king";
        all_cards[i].get_number() = 0;
        all_cards[i].get_value() = 30;
    }
    for (int i = 39; i < 42; i++) {
        all_cards[i].get_type() = "queen";
        all_cards[i].get_number() = 0;
        all_cards[i].get_value() = 40;
    }

    QMovie *gifMovie = new QMovie(":/new/prefix1/Loading.gif");
    ui->label_Loading->setScaledContents(true);
    ui->label_Loading->setMovie(gifMovie);
    gifMovie->start();
    //connect(ui->lineEdit_enter_IP, &QLineEdit::returnPressed, ui->OK, &QPushButton::click);
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
    //connect(this, SIGNAL(client_connected()), Ser)

    //socket->connectToHost("server_ip",8080);
    if(server_or_client==1){
    socket->connectToHost("127.0.0.1",8080);}

    // based on server ip

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
   QString str = QString("%1").arg(QString::fromStdString(buffer.toStdString()));
    if(str=="Hide widgets"){
        ui->label_Loading->hide();
        ui->IP->hide();
        ui->IP_show->hide();
        ui->OK->hide();
        ui->lineEdit_enter_IP->hide();
    }
    else{
    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);

     if(fileType=="message"){
        QString message = QString("%1").arg(QString::fromStdString(buffer.toStdString()));
        emit newMessage(message);
    }
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
  if(socket->waitForConnected()){
   ui->label_Loading->hide();
   ui->IP->hide();
   ui->IP_show->hide();
   ui->OK->hide();
   ui->lineEdit_enter_IP->hide();


   QString str = "Client connected";
   QDataStream socketStream(socket);
   socketStream.setVersion(QDataStream::Qt_5_15);
   QByteArray byteArray = str.toUtf8();
   socketStream << byteArray;

}
  else{
      //design
      QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
      exit(EXIT_FAILURE);
  }
}

void who_start(){ //This funcion gives each player a random card to specify the beginner of the round
    if (server_or_client==1){
        int random_index = rand() % 42;
        if (all_cards[random_index].set_get_isReserved() == false) //if the card is not already given to annother person
        {
            //ui->Card_you
        }
    }
}
void initializing_paths(){
    all_paths[0]=":/new/prefix1/Treasure1.png";
    all_paths[1]=":/new/prefix1/Treasure2.png";
    all_paths[2]=":/new/prefix1/Treasure3.png";
    all_paths[3]=":/new/prefix1/Treasure4.png";
    all_paths[4]=":/new/prefix1/Treasure5.png";
    all_paths[5]=":/new/prefix1/Treasure6.png";
    all_paths[6]=":/new/prefix1/Treasure7.png";
    all_paths[7]=":/new/prefix1/Treasure8.png";
    all_paths[8]=":/new/prefix1/Map1.png";
    all_paths[9]=":/new/prefix1/Map2.png";
    all_paths[10]=":/new/prefix1/Map3.png";
    all_paths[11]=":/new/prefix1/Map4.png";
    all_paths[12]=":/new/prefix1/Map5.png";
    all_paths[13]=":/new/prefix1/Map6.png";
    all_paths[14]=":/new/prefix1/Map7.png";
    all_paths[15]=":/new/prefix1/Map8.png";
    all_paths[16]=":/new/prefix1/Parrot1.png";
    all_paths[17]=":/new/prefix1/Parrot2.png";
    all_paths[18]=":/new/prefix1/Parrot3.png";
    all_paths[19]=":/new/prefix1/Parrot4.png";
    all_paths[20]=":/new/prefix1/Parrot5.png";
    all_paths[21]=":/new/prefix1/Parrot6.png";
    all_paths[22]=":/new/prefix1/Parrot7.png";
    all_paths[23]=":/new/prefix1/Parrot8.png";
    all_paths[24]=":/new/prefix1/Flag1.png";
    all_paths[25]=":/new/prefix1/Flag2.png";
    all_paths[26]=":/new/prefix1/Flag3.png";
    all_paths[27]=":/new/prefix1/Flag4.png";
    all_paths[28]=":/new/prefix1/Flag5.png";
    all_paths[29]=":/new/prefix1/Flag6.png";
    all_paths[30]=":/new/prefix1/Flag7.png";
    all_paths[31]=":/new/prefix1/Flag8.png";
    all_paths[32]=":/new/prefix1/Pirate.png";
    all_paths[33]=":/new/prefix1/Pirate.png";
    all_paths[34]=":/new/prefix1/Pirate.png";
    all_paths[35]=":/new/prefix1/Pirate.png";
    all_paths[36]=":/new/prefix1/King.png";
    all_paths[37]=":/new/prefix1/King.png";
    all_paths[38]=":/new/prefix1/King.png";
    all_paths[39]=":/new/prefix1/Queen.png";
    all_paths[40]=":/new/prefix1/Queen.png";
    all_paths[41]=":/new/prefix1/Queen.png";
}




