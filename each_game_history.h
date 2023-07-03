#ifndef EACH_GAME_HISTORY_H
#define EACH_GAME_HISTORY_H

#include <QWidget>

namespace Ui {
class Each_game_history;
}

class Each_game_history : public QWidget
{
    Q_OBJECT

public:
    explicit Each_game_history(QWidget *parent = nullptr);
    ~Each_game_history();

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::Each_game_history *ui;
};

#endif // EACH_GAME_HISTORY_H
