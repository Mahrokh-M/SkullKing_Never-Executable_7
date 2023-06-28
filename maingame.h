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


namespace Ui {
class mainGame;
}


class mainGame : public QWidget
{
    Q_OBJECT

public:
    explicit mainGame(QWidget *parent = nullptr);
    ~mainGame();
signals:
    void newMessage(QString);
private slots:
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    void displayMessage(const QString& str);

    void on_OK_clicked();

private:
    Ui::mainGame *ui;

    QTcpSocket* socket;
};

#endif // MAINGAME_H
