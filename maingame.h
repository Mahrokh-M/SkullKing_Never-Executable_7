#ifndef MAINGAME_H
#define MAINGAME_H

#include <QWidget>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>
#include <QTcpSocket>
#include<QThread>



namespace Ui {
class mainGame;
}


class mainGame : public QWidget
{
    Q_OBJECT

public:
    explicit mainGame(QWidget *parent = nullptr);
    void who_start();
    void send_message(QString);
    void show_opponent_avatar();
    void handing_out_cards();
    void hide_pushbuttons();
    void show_pushbuttons();
    void connect_pushbutton();
    void compare_cards();
    void end_of_round();
    ~mainGame();
signals:
    void newMessage(QString);
private slots:
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);
    void on_OK_clicked();
    void onButtonClicked();

    void on_OK_Guess_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Exit_clicked();

    void Resume(int);
    void on_change_card_button_clicked();

    void on_Yes_change_clicked();

    void on_No_change_clicked();

protected:
    Ui::mainGame *ui;

    QTcpSocket* socket;
    int seconds_passed;
};


#endif // MAINGAME_H
