#include "maingame.h"
#include "ui_maingame.h"
#include"QMovie"
#include <QHostAddress>
#include <QHostInfo>
#include"globals.h"
#include "card.h"
#include <time.h>
#include<QThread>
#include <chrono>
#include <thread>
#include <QEventLoop>
#include <QTimer>
//#include <cstdlib>

Card all_cards[42]; //An array of all cards we have in the game
QString all_paths[42];
int card1;
int card2;
QString opponent_name;
int opponent_avatar;
void initializing_paths();
mainGame::mainGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainGame)
{
    ui->setupUi(this);
    ui->Who_starts->hide();
    QString avatar_path;
    if(Person->set_get_avatar()==1)
        avatar_path=":/new/prefix1/avatar1.png";
    if(Person->set_get_avatar()==2)
        avatar_path=":/new/prefix1/avatar2.png";
    if(Person->set_get_avatar()==3)
        avatar_path=":/new/prefix1/avatar3.png";
    if(Person->set_get_avatar()==4)
        avatar_path=":/new/prefix1/avatar4.png";
       ui->Avatar_you->setStyleSheet(QString("border-image: url(%1);").arg(avatar_path));
       ui->name_you->setText(Person->set_get_name());
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
     QMovie *gifMovie;
    if(server_or_client==1)
   gifMovie = new QMovie(":/new/prefix1/server loading gif.gif");
    else if(server_or_client==2)
    gifMovie = new QMovie(":/new/prefix1/client loading gif.gif");
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
        ui->OK->setStyleSheet("QPushButton {"
                              "background: qlineargradient(spread: repeat, x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 rgba(184, 121, 255, 255), stop: 1 rgba(143, 255, 236, 255));"
                              "border: none;"
                              "border-radius: 5px;"
                              "color: white;"
                              "font-size: 16px;"
                              "padding: 10px 20px;"
                              "font: 700 16pt Times New Roman;"
                              "border-radius:15px"
                          "}"

                          "QPushButton:hover {"
                              "background: qlineargradient(spread: repeat, x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 rgba(163, 101, 235, 255), stop: 1 rgba(122, 235, 216, 255));"
                          "}"

                          "QPushButton:pressed {"
                              "background: qlineargradient(spread: repeat, x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 rgba(143, 81, 215, 255), stop: 1 rgba(102, 215, 196, 255));"
                          "}");
       ui->IP_show->hide();
       ui->IP->hide();
   }
    socket = new QTcpSocket(this);
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
    if(str.split(" ")[0]=="Clientconnected"){
        QStringList opponent_information=str.split(" ");
        opponent_name=opponent_information[1].split(",")[0];
        opponent_avatar=opponent_information[1].split(",")[1].toInt();
        QString avatar_path_opponent;
        if(opponent_avatar==1)
            avatar_path_opponent=":/new/prefix1/avatar1.png";
        if(opponent_avatar==2)
            avatar_path_opponent=":/new/prefix1/avatar2.png";
        if(opponent_avatar==3)
            avatar_path_opponent=":/new/prefix1/avatar3.png";
        if(opponent_avatar==4)
            avatar_path_opponent=":/new/prefix1/avatar4.png";
        ui->Avatar_opponent->setStyleSheet(QString("border-image: url(%1);").arg(avatar_path_opponent));
        ui->name_opppnent->setText(opponent_name);
        qDebug()<<"1";
        ui->label_Loading->hide();
        ui->IP->hide();
        ui->IP_show->hide();
        ui->OK->hide();
        ui->lineEdit_enter_IP->hide();
        who_start();
    }


    else if(str.split(" ")[0]=="OpponentInformation"){
        QStringList opponent_information=str.split(" ");
        opponent_name=opponent_information[1].split(",")[0];
        opponent_avatar=opponent_information[1].split(",")[1].toInt();
        card2=opponent_information[1].split(",")[2].toInt();
        card1=opponent_information[1].split(",")[3].toInt();
        QMovie *gif;
        if(card1>card2)
         gif = new QMovie(":/new/prefix1/you start.gif");
        else
         gif = new QMovie(":/new/prefix1/you're second.gif");

        ui->Who_starts->setScaledContents(true);
        ui->Who_starts->setMovie(gif);
        ui->Who_starts->show();
        gif->start();
        QString avatar_path_opponent;
        if(opponent_avatar==1)
            avatar_path_opponent=":/new/prefix1/avatar1.png";
        if(opponent_avatar==2)
            avatar_path_opponent=":/new/prefix1/avatar2.png";
        if(opponent_avatar==3)
            avatar_path_opponent=":/new/prefix1/avatar3.png";
        if(opponent_avatar==4)
            avatar_path_opponent=":/new/prefix1/avatar4.png";
        ui->Avatar_opponent->setStyleSheet(QString("border-image: url(%1);").arg(avatar_path_opponent));
        ui->name_opppnent->setText(opponent_name);
        ui->Card_you->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[card1]));
        ui->Card_opponent->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[card2]));
        ui->pushButton_1->hide();
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
        ui->pushButton_4->hide();
        ui->pushButton_5->hide();
        ui->pushButton_6->hide();
        ui->pushButton_7->hide();
        ui->pushButton_8->hide();
        ui->pushButton_9->hide();
        ui->pushButton_10->hide();
        ui->pushButton_11->hide();
        ui->pushButton_12->hide();
        ui->pushButton_13->hide();
        ui->pushButton_14->hide();
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();
        ui->Who_starts->hide();
        ui->Card_you->hide();
        ui->Card_opponent->hide();
        handing_out_cards();
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

void mainGame::on_OK_clicked()
{
  socket->connectToHost(ui->lineEdit_enter_IP->text(),8080);
  if(socket->waitForConnected()){
   ui->label_Loading->hide();
   ui->IP->hide();
   ui->IP_show->hide();
   ui->OK->hide();
   ui->lineEdit_enter_IP->hide();


   QString str = "Clientconnected "+Person->set_get_name()+","+QString::number(Person->set_get_avatar());
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

void mainGame::who_start(){ //This funcion gives each player a random card to specify the beginner of the round
    QString str1 = Person->set_get_name()+","+QString::number(Person->set_get_avatar())+",";
    str1.prepend("OpponentInformation ");
    int random_index;
    while(true){
        random_index = rand() % 8+16;
        if (all_cards[random_index].set_get_isReserved() == false) //if the card is not already given to annother person
        {
            card1=random_index;
            all_cards[random_index].set_get_isReserved()=true;
            ui->Card_you->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[random_index]));
            break;
        }
    }
        while(true){
       random_index = rand() % 8+16;
        if (all_cards[random_index].set_get_isReserved() == false) //if the card is not already given to annother person
        {
            card2=random_index;
            all_cards[random_index].set_get_isReserved()=true;
            ui->Card_opponent->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[random_index]));
            break;
        }
        }
    ui->pushButton_1->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
    ui->pushButton_13->hide();
    ui->pushButton_14->hide();
    str1+= QString::number(card1)+","+QString::number(card2);
    send_message(str1);
    QMovie *gif;
    if(card1>card2)
     gif = new QMovie(":/new/prefix1/you start.gif");
    else
     gif = new QMovie(":/new/prefix1/you're second.gif");
    qDebug()<<"2";
    ui->Who_starts->setScaledContents(true);
    ui->Who_starts->setMovie(gif);
    ui->Who_starts->show();
    ui->label_Loading->hide();
    gif->start();
    qDebug()<<"3";

// NOT Working
//    QThread::msleep(2000);
//    std::this_thread::sleep_for(std::chrono::seconds(2));



    ui->Who_starts->hide();

        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();
        ui->Who_starts->hide();
        ui->Card_you->hide();
        ui->Card_opponent->hide();
//    QTimer::singleShot(1000, this, [&]() {
//            // code to be executed after the delay
//        ui->Who_starts->hide();
//    });



    qDebug()<<"4";
}

void mainGame::send_message(QString input_message){ //This function recieves a messgae and send it to server
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    QByteArray byteArray = input_message.toUtf8();
    socketStream << byteArray;

}

void mainGame::handing_out_cards(){
    int round=1;
    //while (round != 8) {
        for(auto x:all_cards){
            x.set_get_isReserved()=false;
           }
            for (int i = 0; i <2*round;) {
                int random_index = rand() % 42;
                if (all_cards[random_index].set_get_isReserved() == false) //if the card is not already in the list
                {
                    Person->set_get_cards().push_back(random_index);
                    all_cards[random_index].set_get_isReserved() = true;//the card can not be chosen anymore
                    i++;
                }
                sort( Person->set_get_cards().begin(),Person->set_get_cards().end());
                //***sort the cards list so that in qt you can show them in order
            }
            //7,8,6,9,5,10,4,11,3,12,2,13,1,14 order of choosing pushbutton to show cards
            int last_card_shown=0;
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_7->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[0]]));
              ui->pushButton_7->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_8->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[1]]));
              ui->pushButton_8->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_6->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[2]]));
              ui->pushButton_6->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_9->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[3]]));
              ui->pushButton_9->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_5->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[4]]));
              ui->pushButton_5->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_10->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[5]]));
              ui->pushButton_10->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_4->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[6]]));
              ui->pushButton_4->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_11->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[7]]));
              ui->pushButton_11->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_3->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[8]]));
              ui->pushButton_3->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_12->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[9]]));
              ui->pushButton_12->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_2->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[10]]));
              ui->pushButton_2->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_13->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[11]]));
              ui->pushButton_13->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_1->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[12]]));
              ui->pushButton_1->show();
              last_card_shown++;
            }
            if(last_card_shown < Person->set_get_cards().size()){
              ui->pushButton_14->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[Person->set_get_cards()[13]]));
              ui->pushButton_14->show();
              last_card_shown++;
            }

            QString message="";//sends one person cards to the other one so that she won't select it again
            for(auto x: Person->set_get_cards()){
                message+=QString::number(x);
            }
            message.prepend("ReservedCards ");
            send_message(message);
       // }

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




