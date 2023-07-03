#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include "each_game_history.h"
#include<QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
namespace Ui {
class History;
}

class History : public QWidget
{
    Q_OBJECT

private slots:
    void onButtonClicked();
    void on_pushButton_Back_clicked();

public:
    explicit History(QWidget *parent = nullptr);
    ~History();

private:
    Ui::History *ui;
};
class Game_history
{
private:
    QString opponent_username;
    QString opponent_score;
    QString user_score;
    QString result;
    QString game_id; //This is going to be the Date and time which the game is done
    QString screenshot_path; //This holds the path to the screenshot that is taken
public:
    Game_history();
    Game_history(QString, QString, QString, QString, QString);
    QString& set_get_opponent_username();
    QString& set_get_opponent_score();
    QString& set_get_user_score();
    QString& set_get_result();
    QString& set_get_game_id();
    QString& set_get_screenshot_path();
};
#endif // HISTORY_H
