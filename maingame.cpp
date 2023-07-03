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
#include<QtAlgorithms>
#include"QValidator"
#include"mainmenu.h"
#include"thread"
#include <qmath.h>
#include"QFile"
#include <chrono>
#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QFileInfo>
int pause_clicked_count=0;//he should be able to puase twice
bool show_guess=false;//after changing cards you shouldn't show lineedit guess
int Guess;
int Guess_opponent;
int num_win_opponent=0;
int Round=1;
bool begin_set=false; //CHecks who is the beginner of the set
bool has_clicked_OK=false;
bool opponent_has_clicked_OK=false;
int is_turn=0; //Shows whose turn is it
Card all_cards[42]; //An array of all cards we have in the game
QString all_paths[42];
int card1;
int card2;
QString opponent_username;
int opponent_avatar;
QStringList reserved_cards; //This list holds the opponent cards during each round
int both_players_played=0; //To check if both players has played or not
int compare_count=0;//number of times the compare function is called
int Score_you=0;
int Score_opponent=0;
int special_points=0; //The extra point you get when you have King or Queen or Pirate
int opponent_special_points=0;
int which_set_of_round=0;
Game_history new_game_history;
void initializing_paths();
mainGame::mainGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainGame)
{
    ui->setupUi(this);
    Person->set_get_money()=QString::number(Person->set_get_money().toInt()-50);//each person loses 50 coins and then we write the info in file
    QString filePath = "Users.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (auto it = People.begin(); it != People.end(); ++it) {
            out << it->set_get_name() <<"/" <<it->set_get_userName() <<"/"<<it->set_get_phoneNumber()<< "/"<<it->set_get_email()<<"/"<<it->set_get_password()<< "/"<<it->set_get_money()<< "/"<<it->set_get_total_win()<< "/"<<it->set_get_total_lose()<<"/"<<it->set_get_avatar()<<"||";
            for (auto ot = it->set_get_History().begin(); ot != it->set_get_History().begin(); ++ot){
                out <<ot->set_get_opponent_username()<<"/"<<ot->set_get_opponent_score()<<"/"<<ot->set_get_user_score()<<"/"<<ot->set_get_game_id()<<"/"<<ot->set_get_result()<<"/"<<ot->set_get_screenshot_path()<<"!!";
            }
            out<<"\n";
        }
        file.close();
    }
    QIntValidator* validator = new QIntValidator();
    ui->lineEdit_Enter_guess->setValidator(validator);
    ui->Who_starts->hide();
    ui->label_result->hide();
    ui->num_win->hide();
    ui->label_Num_win->hide();
    ui->change_card_button->hide();
    ui->label_decide_change->hide();
    ui->Yes_change->hide();
    ui->No_change->hide();
    ui->Empty_label->hide();
    ui->OK_Guess->setStyleSheet("QPushButton {"
                                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFA500, stop:1 #FF8C00);"
                                "border-style: solid;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: #FFA500;"
                                "color: black;"
                                "font-size: 18px;"
                                "padding: 6px 12px;"
                            "}"

                            "QPushButton:hover {"
                                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFDAB9, stop:1 #FFA500);"
                                "border-color: #FFA500;"
                            "}"

                            "QPushButton:pressed {"
                                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FF8C00, stop:1 #FFA500);"
                                "border-color: #FF8C00;"
                            "}");
    ui->Yes_change->setStyleSheet("QPushButton {"
                                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFA500, stop:1 #FF8C00);"
                                "border-style: solid;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: #FFA500;"
                                "color: black;"
                                "font-size: 18px;"
                                "padding: 6px 12px;"
                            "}"

                            "QPushButton:hover {"
                                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFDAB9, stop:1 #FFA500);"
                                "border-color: #FFA500;"
                            "}"

                            "QPushButton:pressed {"
                                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FF8C00, stop:1 #FFA500);"
                                "border-color: #FF8C00;"
                            "}");
    ui->No_change->setStyleSheet("QPushButton {"
                                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFA500, stop:1 #FF8C00);"
                                "border-style: solid;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: #FFA500;"
                                "color: black;"
                                "font-size: 18px;"
                                "padding: 6px 12px;"
                            "}"

                            "QPushButton:hover {"
                                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFDAB9, stop:1 #FFA500);"
                                "border-color: #FFA500;"
                            "}"

                            "QPushButton:pressed {"
                                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FF8C00, stop:1 #FFA500);"
                                "border-color: #FF8C00;"
                            "}");
    ui->pushButton_Stop->hide();
    ui->pushButton_Exit->setStyleSheet(QString("border-image: url(:/new/prefix1/Exit_Button.png);"));
    ui->pushButton_Exit->hide();
    ui->change_card_button->setStyleSheet(QString("border-image: url(:/new/prefix1/Change_cards.png);"));
    ui->pushButton_Stop->setStyleSheet(QString("color:transparent; border-image: url(:/new/prefix1/StopButton.png);"));
    ui->pushButton_Stop->setText("Pause");
    ui->Point_you->setText(QString::number(Score_you));
    ui->Point_opponent->setText(QString::number(Score_opponent));
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
       ui->name_you->setText(Person->set_get_userName());
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
        all_cards[i].get_value() = 20;
    }
    for (int i = 39; i < 42; i++) {
        all_cards[i].get_type() = "queen";
        all_cards[i].get_number() = 0;
        all_cards[i].get_value() = 20;
    }
     QMovie *gifMovie;
    if(server_or_client==1)
   gifMovie = new QMovie(":/new/prefix1/server loading gif.gif");
    else if(server_or_client==2)
    gifMovie = new QMovie(":/new/prefix1/client loading gif.gif");
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
    ui->OK_Guess->hide();
    ui->lineEdit_Enter_guess->hide();
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &mainGame::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &mainGame::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &mainGame::displayError);
    connect_pushbutton(); //Connect signal of all pushbuttons to one slot
    connect(ui->lineEdit_enter_IP, &QLineEdit::returnPressed, ui->OK, &QPushButton::click);
    connect(ui->lineEdit_Enter_guess, &QLineEdit::returnPressed, ui->OK_Guess, &QPushButton::click);

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

void mainGame::readSocket()//this function reads all the messages
{
    QByteArray buffer;
    buffer=socket->readAll();
   QString str = QString("%1").arg(QString::fromStdString(buffer.toStdString()));
    if(str.split(" ")[0]=="Clientconnected"){
        QStringList opponent_information=str.split(" ");
        opponent_username=opponent_information[1].split(",")[0];
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
        ui->name_opppnent->setText(opponent_username);
        ui->label_Loading->hide();
        ui->pushButton_Stop->show();
        ui->pushButton_Exit->show();
        ui->IP->hide();
        ui->IP_show->hide();
        ui->OK->hide();
        ui->lineEdit_enter_IP->hide();
        ui->num_win->show();
        ui->label_Num_win->show();
        ui->change_card_button->show();
        who_start();
    }

    else if(str.split(" ")[0]=="ReservedCards"){
        reserved_cards=str.split(" ")[1].split(",");
        handing_out_cards();
    }

    else if(str.split(" ")[0]=="OpponentInformation"){
        QStringList opponent_information=str.split(" ");
        opponent_username=opponent_information[1].split(",")[0];
        opponent_avatar=opponent_information[1].split(",")[1].toInt();
        card2=opponent_information[1].split(",")[2].toInt();
        card1=opponent_information[1].split(",")[3].toInt();
        QMovie *gif;
        if(card1>card2){
            begin_set=true;
            is_turn=1;
            gif = new QMovie(":/new/prefix1/you start.gif");
        }
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
        ui->name_opppnent->setText(opponent_username);
        ui->Card_you->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[card1]));
        ui->Card_opponent->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[card2]));
        hide_pushbuttons();
        QEventLoop loop;
        QTimer::singleShot(3000, &loop, &QEventLoop::quit);
        loop.exec();
        ui->Who_starts->hide();
        ui->Card_you->hide();
        ui->Card_opponent->hide();
        handing_out_cards();
    }

    else if(str.split(" ")[0]=="Opponent_played_card"){
        is_turn=1;
        both_players_played=str.split(" ")[2].toInt();
        QString opponent_card=str.split(" ")[1];
        card2=opponent_card.toInt();
        ui->Card_opponent->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[opponent_card.toInt()]));
        ui->Card_opponent->show();
        if(both_players_played==2){
            both_players_played=0;
            QString message="call compare function";
            send_message(message);
            compare_cards();
        }
    }

    else if(str.split(" ")[0]=="Opponent_ok_clicked"){
        opponent_has_clicked_OK=true; //Do not forget to make this false end of each round!
        Guess_opponent=str.split(" ")[1].toInt();
    }

    else if(str=="call compare function"){
        both_players_played=0;
        compare_cards();

    }

    else if(str.split(" ")[0]=="score_opponent"){
        Score_opponent=str.split(" ")[1].toInt();
    }

    else if(str.split(" ")[0]=="Stop_Resume"){
        if(str.split(" ")[1]=="show_gif"){
           QMovie *gif;
           gif = new QMovie(":/new/prefix1/Stop_gif.gif");
           ui->label_Loading->setScaledContents(true);
           ui->label_Loading->setMovie(gif);
           ui->label_Loading->show();
           ui->label_Loading->raise();
           ui->pushButton_Exit->raise();
           gif->start();
        }
        else if(str.split(" ")[1]=="hide_gif"){
            ui->label_Loading->hide();
        }
    }

    else if(str=="Exit Button Clicked"){
        new_game_history.set_get_user_score()=QString::number(Score_you);
        new_game_history.set_get_opponent_score()=QString::number(Score_opponent);
        new_game_history.set_get_opponent_username()=opponent_username;
        new_game_history.set_get_result()="Win";
        auto date_of_game = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(date_of_game);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
        new_game_history.set_get_game_id()=QString::fromUtf8(buffer);
        Person->set_get_History().prepend(new_game_history); //Add the new game to the list of all the user's game
        ui->label_result->setStyleSheet(QString("border-image: url(%1);").arg(":/new/prefix1/You Win.png"));
        ui->label_result->raise();
        ui->label_result->show();
        QEventLoop loop;
        QTimer::singleShot(3000, &loop, &QEventLoop::quit);
        loop.exec();
        QString filePath = "Users.txt";
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            for (auto it = People.begin(); it != People.end(); ++it) {
                out << it->set_get_name() <<"/" <<it->set_get_userName() <<"/"<<it->set_get_phoneNumber()<< "/"<<it->set_get_email()<<"/"<<it->set_get_password()<< "/"<<it->set_get_money()<< "/"<<it->set_get_total_win()<< "/"<<it->set_get_total_lose()<<"/"<<it->set_get_avatar()<<"||";
                for (auto ot = it->set_get_History().begin(); ot != it->set_get_History().begin(); ++ot){
                    out <<ot->set_get_opponent_username()<<"/"<<ot->set_get_opponent_score()<<"/"<<ot->set_get_user_score()<<"/"<<ot->set_get_game_id()<<"/"<<ot->set_get_result()<<"/"<<ot->set_get_screenshot_path()<<"!!";
                }
                out<<"\n";
            }
            file.close();
        }
        this->close();
        MainMenu *main_page=new MainMenu();
        main_page->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        main_page->show();
    }

    else if(str=="change cards"){
        ui->label_decide_change->show();
        ui->Yes_change->show();
        ui->No_change->show();
        ui->Empty_label->show();
    }

    else if(str=="no_change"){
        ui->label_decide_change->hide();
        ui->Yes_change->hide();
        ui->No_change->hide();
        ui->Empty_label->hide();
        QMessageBox messageBox;
        messageBox.setWindowTitle("Error");
        messageBox.setIcon(QMessageBox::Information);
        messageBox.setStyleSheet("QMessageBox { background-color: #c96f30; color: white; font-size: 16px; font-weight: bold; }");
        QAbstractButton* okButton = messageBox.addButton("Ok", QMessageBox::AcceptRole);
        okButton->setStyleSheet("background-color: #ff8b3d; color: black; font-size: 16px; font-weight: bold;");
        messageBox.setText("Your request was rejected!");
        messageBox.exec();
    }

    else if(str.split(" ")[0]=="yes_change"){
        int opponent_index=str.split(" ")[1].toInt();
        int random_index = rand() % (Person->set_get_cards().size());
        QString message="card_to_change "+QString::number(Person->set_get_cards()[random_index]);//send message to other user to change his card with the given card
        Person->set_get_cards().erase(Person->set_get_cards().begin()+random_index);
        Person->set_get_cards().shrink_to_fit();
        send_message(message);
        Person->set_get_cards().push_back(opponent_index);
        show_guess=true;
        ui->label_decide_change->hide();
        ui->Yes_change->hide();
        ui->No_change->hide();
        ui->Empty_label->hide();
        hide_pushbuttons();
        show_pushbuttons();
    }

    else if(str.split(" ")[0]=="card_to_change"){
        int opponent_index=str.split(" ")[1].toInt();
        Person->set_get_cards().push_back(opponent_index);
        show_guess=true;
        ui->label_decide_change->hide();
        ui->Yes_change->hide();
        ui->No_change->hide();
        ui->Empty_label->hide();
        hide_pushbuttons();
        show_pushbuttons();
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

void mainGame::on_OK_clicked()//when client connects
{
  socket->connectToHost(ui->lineEdit_enter_IP->text(),8080);
  if(socket->waitForConnected()){
   ui->label_Loading->hide();
   ui->pushButton_Stop->show();
   ui->pushButton_Exit->show();
   ui->change_card_button->show();
   ui->IP->hide();
   ui->IP_show->hide();
   ui->OK->hide();
   ui->lineEdit_enter_IP->hide();
   ui->num_win->show();
   ui->label_Num_win->show();
   hide_pushbuttons();
   QString str = "Clientconnected "+Person->set_get_userName()+","+QString::number(Person->set_get_avatar());
//   QDataStream socketStream(socket);
//   socketStream.setVersion(QDataStream::Qt_5_15);
   QByteArray byteArray = str.toUtf8();
   socket->write(byteArray);

}
  else{
      //design
      QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
      exit(EXIT_FAILURE);
  }
}

void mainGame::who_start(){ //This funcion gives each player a random card to specify the beginner of the round
    QString str1 = Person->set_get_userName()+","+QString::number(Person->set_get_avatar())+",";
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
    str1+= QString::number(card1)+","+QString::number(card2);
    send_message(str1);
    if(server_or_client==1)
        hide_pushbuttons();
    QMovie *gif;
    if(card1>card2){
        is_turn=1;
        gif = new QMovie(":/new/prefix1/you start.gif");
        begin_set=true;
    }
    else
     gif = new QMovie(":/new/prefix1/you're second.gif");
    ui->Who_starts->setScaledContents(true);
    ui->Who_starts->setMovie(gif);
    ui->Who_starts->show();
    ui->label_Loading->hide();
    gif->start();

// NOT Working
//    QThread::msleep(2000);
//    std::this_thread::sleep_for(std::chrono::seconds(2));

        QEventLoop loop;
        QTimer::singleShot(3000, &loop, &QEventLoop::quit);
        loop.exec();
        ui->Who_starts->hide();
        ui->Card_you->hide();
        ui->Card_opponent->hide();
//    QTimer::singleShot(1000, this, [&]() {
//            // code to be executed after the delay
//        ui->Who_starts->hide();
//    });


}

void mainGame::send_message(QString input_message){ //This function recieves a messgae and send it to server
//    QDataStream socketStream(socket);
//    socketStream.setVersion(QDataStream::Qt_5_15);
    QByteArray byteArray = input_message.toUtf8();
    socket->write(byteArray);
    socket->waitForBytesWritten();

}

void mainGame::handing_out_cards(){//giving random cards to each player
          for(int i=0;i<42;i++){
              all_cards[i].set_get_isReserved()=false;
          }
            if(server_or_client==1){
                for(auto x:reserved_cards){
                    all_cards[x.toInt()].set_get_isReserved()=true;
                }
            }
            for (int i = 0; i <2*Round;) {
                int random_index = rand() % 42;
                if (all_cards[random_index].set_get_isReserved() == false) //if the card is not already in the list
                {
                    Person->set_get_cards().push_back(random_index);
                    all_cards[random_index].set_get_isReserved() = true;//the card can not be chosen anymore
                    i++;
                }
            }
            sort( Person->set_get_cards().begin(),Person->set_get_cards().end());
            //***sort the cards list so that you can show them in order
            show_pushbuttons();

            if(server_or_client==2){
               QString message="";//sends one person cards to the other one so that she won't select it again
               bool flag=false;
               for(auto x: Person->set_get_cards()){
                   if(flag)
                       message+=",";
                   flag=true;
                   message+=QString::number(x);
               }
               message.prepend("ReservedCards ");
               send_message(message);
            }

}

void initializing_paths(){//setting paths for each photo in an array so that the all cards array can find the address to each card's photo
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

void mainGame::hide_pushbuttons(){//hiding all cards pushbuttons
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
}

void mainGame::show_pushbuttons(){//setting pictures for card pushbuttons from the middle
    //7,8,6,9,5,10,4,11,3,12,2,13,1,14 order of choosing pushbutton to show cards
      int last_card_shown=0;
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_7->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[0]]));
        ui->pushButton_7->setText(QString::number(Person->set_get_cards()[0]));
        ui->pushButton_7->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_8->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[1]]));
        ui->pushButton_8->setText(QString::number(Person->set_get_cards()[1]));
        ui->pushButton_8->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_6->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[2]]));
        ui->pushButton_6->setText(QString::number(Person->set_get_cards()[2]));
        ui->pushButton_6->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_9->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[3]]));
        ui->pushButton_9->setText(QString::number(Person->set_get_cards()[3]));
        ui->pushButton_9->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_5->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[4]]));
        ui->pushButton_5->setText(QString::number(Person->set_get_cards()[4]));
        ui->pushButton_5->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_10->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[5]]));
        ui->pushButton_10->setText(QString::number(Person->set_get_cards()[5]));
        ui->pushButton_10->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_4->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[6]]));
        ui->pushButton_4->setText(QString::number(Person->set_get_cards()[6]));
        ui->pushButton_4->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_11->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[7]]));
        ui->pushButton_11->setText(QString::number(Person->set_get_cards()[7]));
        ui->pushButton_11->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_3->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[8]]));
        ui->pushButton_3->setText(QString::number(Person->set_get_cards()[8]));
        ui->pushButton_3->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_12->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[9]]));
        ui->pushButton_12->setText(QString::number(Person->set_get_cards()[9]));
        ui->pushButton_12->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_2->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[10]]));
        ui->pushButton_2->setText(QString::number(Person->set_get_cards()[10]));
        ui->pushButton_2->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_13->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[11]]));
        ui->pushButton_13->setText(QString::number(Person->set_get_cards()[11]));
        ui->pushButton_13->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_1->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[12]]));
        ui->pushButton_1->setText(QString::number(Person->set_get_cards()[12]));
        ui->pushButton_1->show();
        last_card_shown++;
      }
      if(last_card_shown < Person->set_get_cards().size()){
        ui->pushButton_14->setStyleSheet(QString("color:transparent; border-image: url(%1);").arg(all_paths[Person->set_get_cards()[13]]));
        ui->pushButton_14->setText(QString::number(Person->set_get_cards()[13]));
        ui->pushButton_14->show();
        last_card_shown++;
      }
      if(!show_guess){
        ui->OK_Guess->show();
        ui->lineEdit_Enter_guess->show();}
      else
        show_guess=false;
}

void mainGame::connect_pushbutton(){//connecting card pushbuttons to one slot
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

void mainGame::onButtonClicked(){ //delete chosen card from user's cards list and show it in center
    QPushButton *clicked_button = qobject_cast<QPushButton *>(sender());
    int chosen_card=clicked_button->text().toInt();
    card1=chosen_card;
    if(is_turn==1&&has_clicked_OK==true&&opponent_has_clicked_OK==true){
       bool flag=false;
       for(const auto&x:Person->set_get_cards()){
         if(all_cards[card2].get_type()==all_cards[x].get_type()){
             flag=true;
             break;
         }
       }
      if((all_cards[card1].get_type()==all_cards[card2].get_type())||(all_cards[card1].get_type()!=all_cards[card2].get_type()&&(!flag))||(card1>=32&&card1<=41)||(begin_set)){
         both_players_played++;
         QString message="Opponent_played_card "+QString::number(chosen_card)+" "+QString::number(both_players_played);
         send_message(message);
         int index=Person->set_get_cards().indexOf(chosen_card);
         Person->set_get_cards().erase(Person->set_get_cards().begin()+index);
         Person->set_get_cards().shrink_to_fit();
         clicked_button->hide();
         ui->Card_you->setStyleSheet(QString("border-image: url(%1);").arg(all_paths[chosen_card]));
         ui->Card_you->show();
         is_turn=0;}
    else{
        QMessageBox messageBox;
        messageBox.setWindowTitle("Error");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setStyleSheet("QMessageBox { background-color: #c96f30; color: white; font-size: 16px; font-weight: bold; }");
        QAbstractButton* okButton = messageBox.addButton("Ok", QMessageBox::AcceptRole);
        okButton->setStyleSheet("background-color: #ff8b3d; color: black; font-size: 16px; font-weight: bold;");
        messageBox.setText("Wrong card played!");
        messageBox.exec();
    }
  }
}

void mainGame::on_OK_Guess_clicked()//telling other user that you have guessed how many rounds you will win
{
    QMessageBox messageBox;
    messageBox.setWindowTitle("Error");
    messageBox.setIcon(QMessageBox::Critical);
    messageBox.setStyleSheet("QMessageBox { background-color: #c96f30; color: white; font-size: 16px; font-weight: bold; }");
    QAbstractButton* okButton = messageBox.addButton("Ok", QMessageBox::AcceptRole);
    okButton->setStyleSheet("background-color: #ff8b3d; color: black; font-size: 16px; font-weight: bold;");
    if(!ui->lineEdit_Enter_guess->text().isEmpty()&&ui->lineEdit_Enter_guess->text().toInt()<=Round*2){
        has_clicked_OK=true;
        Guess=ui->lineEdit_Enter_guess->text().toInt();
        ui->OK_Guess->hide();
        ui->lineEdit_Enter_guess->hide();
        QString message="Opponent_ok_clicked "; //Telling other user has clicked
        message+=QString::number(Guess);
        ui->lineEdit_Enter_guess->clear();
        send_message(message);
    }
    else if(ui->lineEdit_Enter_guess->text().toInt()>Round*2){
        messageBox.setText("Invalid Prediction!");
        messageBox.exec();
    }
    else{
        messageBox.setText("Enter Your Prediction!");
        messageBox.exec();
    }
}

void mainGame::compare_cards(){//comparing cards and giving points
     which_set_of_round++;
    if(Round==7 && which_set_of_round==2*Round){
//        QScreen *screen = QGuiApplication::primaryScreen();
//        // Capture the screenshot
//        QPixmap screenshot = screen->grabWindow(0);
//        // Save the screenshot to a file
//        QString str1="screenshot";
//        QString str2=QString::number(Person->set_get_History().size()+1);
//        QString str3=".png";
//        QString filename = str1+str2+str3;
//        screenshot.save(filename);
//        // Get the path of the saved file
//        QString path = QFileInfo(filename).absoluteFilePath();
//        new_game_history.set_get_screenshot_path()=path;
        // Get the geometry of the widget
        QRect geometry = this->geometry();

        // Get the list of available screens and select the primary screen
        QList<QScreen*> screens = QApplication::screens();
        QScreen* primaryScreen = screens.at(0);

        // Take a screenshot of the area within the widget geometry
        QPixmap screenshot = primaryScreen->grabWindow(0, geometry.x(), geometry.y(), geometry.width(), geometry.height());
         QString str1="screenshot";
         QString str2=QString::number(Person->set_get_History().size()+1);
         QString str3=".png";
         QString filename = str1+str2+str3;
         screenshot.save(filename);
         // Get the path of the saved file
         QString path = QFileInfo(filename).absoluteFilePath();
         new_game_history.set_get_screenshot_path()=path;

    }
    if(all_cards[card1].get_value()>all_cards[card2].get_value()){  //Counting opponent points
            if(all_cards[card1].get_type()=="pirate" || all_cards[card2].get_type()=="pirate"){
                    special_points+=10;}
            if(all_cards[card1].get_type()=="king" || all_cards[card2].get_type()=="king"){
                    special_points+=15;}
            if(all_cards[card1].get_type()=="queen" || all_cards[card2].get_type()=="queen"){
                    special_points+=20;}
        Person->set_get_num_win()++;
        is_turn=1;
        begin_set=true;
    }

    else if(all_cards[card1].get_value()<all_cards[card2].get_value()){  //Counting opponent points
        if(all_cards[card1].get_type()=="pirate" || all_cards[card2].get_type()=="pirate"){
                 opponent_special_points+=10;}
        if(all_cards[card1].get_type()=="king" || all_cards[card2].get_type()=="king"){
                opponent_special_points+=15;}
        if(all_cards[card1].get_type()=="queen" || all_cards[card2].get_type()=="queen"){
                 opponent_special_points+=20;}
        num_win_opponent++;
        is_turn=0;
        begin_set=false;
    }

    else if(all_cards[card1].get_value()==all_cards[card2].get_value()){
        if(all_cards[card1].get_type()==all_cards[card2].get_type()){
            if(all_cards[card1].get_type()=="pirate" && all_cards[card2].get_type()=="pirate"){
                if(begin_set){
                    special_points+=20;
                    Person->set_get_num_win()++;
                    is_turn=1;
                begin_set=true;}
                else{
                       opponent_special_points+=20;
                       num_win_opponent++;
                       is_turn=0;
                begin_set=false;}
                    }
            else if(all_cards[card1].get_type()=="king" && all_cards[card2].get_type()=="king"){
                    if(begin_set){
                        special_points+=30;
                        Person->set_get_num_win()++;
                        is_turn=1;
                        begin_set=true;}
                     else{
                        opponent_special_points+=30;
                        num_win_opponent++;
                        is_turn=0;
                    begin_set=false;}
                    }
            else if(all_cards[card1].get_type()=="queen" && all_cards[card2].get_type()=="queen"){
                     if(begin_set){
                        special_points+=40;
                        Person->set_get_num_win()++;
                        is_turn=1;
                     begin_set=true;}
                     else{
                        opponent_special_points+=40;
                        num_win_opponent++;
                        is_turn=0;
                     begin_set=false;}
                    }
        }
        else{
                 if(all_cards[card1].get_type()=="pirate" && all_cards[card2].get_type()=="queen"){
                     Person->set_get_num_win()++;
                     is_turn=1;
                     begin_set=true;
                  }
                 else if(all_cards[card1].get_type()=="pirate" && all_cards[card2].get_type()=="king"){
                     num_win_opponent++;
                     is_turn=0;
                     begin_set=false;
                  }
                 else if(all_cards[card1].get_type()=="queen" && all_cards[card2].get_type()=="pirate"){
                     num_win_opponent++;
                     is_turn=0;
                     begin_set=false;
                 }
                 else if(all_cards[card1].get_type()=="queen" && all_cards[card2].get_type()=="king"){
                     Person->set_get_num_win()++;
                     is_turn=1;
                     begin_set=true;
                 }
                 else if(all_cards[card1].get_type()=="king" && all_cards[card2].get_type()=="pirate"){
                     Person->set_get_num_win()++;
                     is_turn=1;
                     begin_set=true;
                 }
                 else if(all_cards[card1].get_type()=="king" && all_cards[card2].get_type()=="queen"){
                     num_win_opponent++;
                     is_turn=0;
                     begin_set=false;
                 }
                 if(begin_set){
                     if(all_cards[card1].get_type()=="pirate" || all_cards[card2].get_type()=="pirate"){
                             special_points+=10;}
                     if(all_cards[card1].get_type()=="king" || all_cards[card2].get_type()=="king"){
                             special_points+=15;}
                     if(all_cards[card1].get_type()=="queen" || all_cards[card2].get_type()=="queen"){
                             special_points+=20;}
                 }
                 else{
                     if(all_cards[card1].get_type()=="pirate" || all_cards[card2].get_type()=="pirate"){
                              opponent_special_points+=10;}
                     if(all_cards[card1].get_type()=="king" || all_cards[card2].get_type()=="king"){
                             opponent_special_points+=15;}
                     if(all_cards[card1].get_type()=="queen" || all_cards[card2].get_type()=="queen"){
                              opponent_special_points+=20;}
                     }
       }
    }
    Score_you+=special_points;
    Score_opponent+=opponent_special_points;
    special_points=0;
    opponent_special_points=0;
    ui->num_win->setText(QString::number(Person->set_get_num_win()));
    ui->Point_you->setText(QString::number(Score_you));
    ui->Point_opponent->setText(QString::number(Score_opponent));
    QEventLoop loop;
    QTimer::singleShot(1000, &loop, &QEventLoop::quit);
    loop.exec();
    ui->Card_you->hide();
    ui->Card_opponent->hide();
    compare_count++;
    if(compare_count==2*Round){
        end_of_round();
    }
}

void mainGame::end_of_round(){//things to do at the end of each round and the end of game
       QMovie *gifMovie;
    if(Person->set_get_num_win()==Guess){
        if(Guess==0){
            Score_you+=Round*10;
        }
        else{
            Score_you+=Guess*10;
        }
       gifMovie = new QMovie(":/new/prefix1/one point.gif");
    }

    else{
        if(Guess==0){
            Score_you-=Round*10;
        }
        else{
            Score_you-=qAbs(Person->set_get_num_win()-Guess)*10;
        }
        gifMovie = new QMovie(":/new/prefix1/no point.gif");
    }
    if(num_win_opponent==Guess_opponent){
        if(Guess==0){
            Score_opponent+=Round*10;
        }
        else{
            Score_opponent+=Guess_opponent*10;
        }
    }

    else{
        if(Guess_opponent==0){
            Score_opponent-=Round*10;
        }
        else{
            Score_opponent-=qAbs(num_win_opponent-Guess_opponent)*10; //Difference between guess and number of won set
        }
    }
    special_points=0;
    opponent_special_points=0;
    ui->Point_you->setText(QString::number(Score_you));
    ui->Point_opponent->setText(QString::number(Score_opponent));
    ui->Who_starts->setScaledContents(true);
    ui->Who_starts->setMovie(gifMovie);
    ui->Who_starts->show();
    gifMovie->start();
    QEventLoop loop;
    QTimer::singleShot(1000, &loop, &QEventLoop::quit);
    loop.exec();
    QMovie *gif;
    if(Round==1){
    gif = new QMovie(":/new/prefix1/Round 2.gif");
    ui->Who_starts->setScaledContents(true);
    ui->Who_starts->setMovie(gif);
    ui->Who_starts->show();
     gif->start();}
    if(Round==2){
    gif = new QMovie(":/new/prefix1/Round 3.gif");
    ui->Who_starts->setScaledContents(true);
    ui->Who_starts->setMovie(gif);
    ui->Who_starts->show();
     gif->start();}
    if(Round==3){
    gif = new QMovie(":/new/prefix1/Round 4.gif");
    ui->Who_starts->setScaledContents(true);
    ui->Who_starts->setMovie(gif);
    ui->Who_starts->show();
     gif->start();}
    if(Round==4){
    gif = new QMovie(":/new/prefix1/Round 5.gif");
    ui->Who_starts->setScaledContents(true);
    ui->Who_starts->setMovie(gif);
    ui->Who_starts->show();
     gif->start();}
    if(Round==5){
    gif = new QMovie(":/new/prefix1/Round 6.gif");
    ui->Who_starts->setScaledContents(true);
    ui->Who_starts->setMovie(gif);
    ui->Who_starts->show();
     gif->start();}
    if(Round==6){
    gif = new QMovie(":/new/prefix1/Round 7.gif");
    ui->Who_starts->setScaledContents(true);
    ui->Who_starts->setMovie(gif);
    ui->Who_starts->show();
     gif->start();}
    QEventLoop lOop;
    QTimer::singleShot(1000, &lOop, &QEventLoop::quit);
    lOop.exec();
    ui->Who_starts->hide();
    ui->Card_you->hide();
    ui->Card_opponent->hide();

    if(Round!=7){
        Round++;
        compare_count=0;
        which_set_of_round=0;
        Person->set_get_num_win()=0;
        num_win_opponent=0;
        has_clicked_OK=false;
        opponent_has_clicked_OK=false;
        ui->num_win->setText(QString::number(Person->set_get_num_win()));
        if(server_or_client==2)
        handing_out_cards();
    }
    else if(Round==7){ //end of game :)

        new_game_history.set_get_user_score()=QString::number(Score_you);
        new_game_history.set_get_opponent_score()=QString::number(Score_opponent);
        new_game_history.set_get_opponent_username()=opponent_username;
        auto date_of_game = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(date_of_game);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
        new_game_history.set_get_game_id()=QString::fromUtf8(buffer);

        if(Score_you >Score_opponent){
            new_game_history.set_get_result()="Win";
            Person->set_get_money()=QString::number(Person->set_get_money().toInt()+100);//winner wins 100 coins and then we write the info in file
            QString filePath = "Users.txt";
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&file);
                for (auto it = People.begin(); it != People.end(); ++it) {
                    out << it->set_get_name() <<"/" <<it->set_get_userName() <<"/"<<it->set_get_phoneNumber()<< "/"<<it->set_get_email()<<"/"<<it->set_get_password()<< "/"<<it->set_get_money()<< "/"<<it->set_get_total_win()<< "/"<<it->set_get_total_lose()<<"/"<<it->set_get_avatar()<<"||";
                    for (auto ot = it->set_get_History().begin(); ot != it->set_get_History().begin(); ++ot){
                        out <<ot->set_get_opponent_username()<<"/"<<ot->set_get_opponent_score()<<"/"<<ot->set_get_user_score()<<"/"<<ot->set_get_game_id()<<"/"<<ot->set_get_result()<<"/"<<ot->set_get_screenshot_path()<<"!!";
                    }
                    out<<"\n";
                }
                file.close();
            }
          ui->label_result->setStyleSheet(QString("border-image: url(%1);").arg(":/new/prefix1/You Win.png"));
          //ui->pushButton_Stop->hide();
          //ui->pushButton_Exit->hide();

        }
        else if(Score_opponent>Score_you){
            new_game_history.set_get_result()="Lose";
            //You lost and opponent won gif           
            ui->label_result->setStyleSheet(QString("border-image: url(%1);").arg(":/new/prefix1/You Lost.png"));

        }
        else{
            new_game_history.set_get_result()="Tie";
            //no one win gif
            ui->label_result->setStyleSheet(QString("border-image: url(%1);").arg(":/new/prefix1/Tie.png"));

        }
        Person->set_get_History().prepend(new_game_history); //Add the new game to the list of all the user's game
        QString filePath = "Users.txt";
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            for (auto it = People.begin(); it != People.end(); ++it) {
                out << it->set_get_name() <<"/" <<it->set_get_userName() <<"/"<<it->set_get_phoneNumber()<< "/"<<it->set_get_email()<<"/"<<it->set_get_password()<< "/"<<it->set_get_money()<< "/"<<it->set_get_total_win()<< "/"<<it->set_get_total_lose()<<"/"<<it->set_get_avatar()<<"||";
                for (auto ot = it->set_get_History().begin(); ot != it->set_get_History().begin(); ++ot){
                    out <<ot->set_get_opponent_username()<<"/"<<ot->set_get_opponent_score()<<"/"<<ot->set_get_user_score()<<"/"<<ot->set_get_game_id()<<"/"<<ot->set_get_result()<<"/"<<ot->set_get_screenshot_path()<<"!!";
                }
                out<<"\n";
            }
            file.close();
        }
        ui->label_result->raise();
        ui->label_result->show();
        QEventLoop loop;
        QTimer::singleShot(3000, &loop, &QEventLoop::quit);
        loop.exec();
        this->close();
        MainMenu *main_page=new MainMenu();
        main_page->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        main_page->show();
    }

}

void mainGame::on_pushButton_Stop_clicked()//pausing the game
{
    QTimer* t=new QTimer(this);

        if(ui->pushButton_Stop->text()=="Pause"){
           pause_clicked_count++;
           if(pause_clicked_count<=2){
           ui->pushButton_Stop->setStyleSheet(QString("color:transparent; border-image: url(:/new/prefix1/ResumeButton.png);"));
           ui->pushButton_Stop->setText("Resume");
           QString message;
           message="Stop_Resume show_gif"; //Tell the other user to stop the game and show gif
           send_message(message);
           QMovie *gif;
           gif = new QMovie(":/new/prefix1/Stop_gif.gif");
           ui->label_Loading->setScaledContents(true);
           ui->label_Loading->setMovie(gif);
           ui->label_Loading->show();
           ui->label_Loading->raise();
           ui->pushButton_Stop->raise(); //This brings the button to front
           ui->pushButton_Exit->raise();
          // int seconds_passed=20;

           connect(t, SIGNAL(timeout()), this, SLOT(Resume(seconds_passed)));
           t->start(1000);
           seconds_passed=20;
           gif->start();
//           connect(gif, &QMovie::frameChanged, [=](int frameNumber) {
//               if (frameNumber == gif->frameCount() - 1) {
//                       Resume();
//               }
//        });
           }

        }
        else if(ui->pushButton_Stop->text()=="Resume"){
            Resume(0);
            delete t;
        }

}

void mainGame::Resume(int seconds_passed){//resuming the game

    if(seconds_passed==0){
       QString message;
       message="Stop_Resume hide_gif"; //Tell the other user to to stop the pause and continue game
       send_message(message);
       ui->label_Loading->hide();
       ui->pushButton_Stop->setStyleSheet(QString("color:transparent; border-image: url(:/new/prefix1/StopButton.png);"));
       ui->pushButton_Stop->setText("Pause");
    }
    else seconds_passed--;
}

void mainGame::on_pushButton_Exit_clicked()//exit from game
{
    new_game_history.set_get_user_score()=QString::number(Score_you);
    new_game_history.set_get_opponent_score()=QString::number(Score_opponent);
    new_game_history.set_get_opponent_username()=opponent_username;
    new_game_history.set_get_result()="Lose";
    auto date_of_game = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(date_of_game);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    new_game_history.set_get_game_id()=QString::fromUtf8(buffer);
    Person->set_get_History().prepend(new_game_history); //Add the new game to the list of all the user's game
    QString message="Exit Button Clicked";
    send_message(message);
    ui->label_result->setStyleSheet(QString("border-image: url(%1);").arg(":/new/prefix1/You Lost.png"));
    ui->label_result->raise();
    ui->label_result->show();
    QEventLoop loop;
    QTimer::singleShot(3000, &loop, &QEventLoop::quit);
    loop.exec();
    this->close();
    MainMenu *main_page=new MainMenu();
    main_page->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    main_page->show();
}

void mainGame::on_change_card_button_clicked()//changing cards request
{
    QMessageBox messageBox;
    messageBox.setWindowTitle("Error");
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setStyleSheet("QMessageBox { background-color: #c96f30; color: white; font-size: 16px; font-weight: bold; }");
    QAbstractButton* okButton = messageBox.addButton("Ok", QMessageBox::AcceptRole);
    okButton->setStyleSheet("background-color: #ff8b3d; color: black; font-size: 16px; font-weight: bold;");
    messageBox.setText("Your request was sent!");
    messageBox.exec();
    QString message="change cards";
    send_message(message);
    ui->Empty_label->show();
}

void mainGame::on_Yes_change_clicked()
{
    int random_index = rand() % (Person->set_get_cards().size());
    QString message="yes_change "+QString::number(Person->set_get_cards()[random_index]);
    Person->set_get_cards().erase(Person->set_get_cards().begin()+random_index);
    Person->set_get_cards().shrink_to_fit();
    send_message(message);
    ui->label_decide_change->hide();
    ui->Yes_change->hide();
    ui->No_change->hide();
    ui->Empty_label->hide();

}

void mainGame::on_No_change_clicked()
{
    ui->label_decide_change->hide();
    ui->Yes_change->hide();
    ui->No_change->hide();
    ui->Empty_label->hide();
    QString message="no_change";
    send_message(message);
}

