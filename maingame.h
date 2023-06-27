#ifndef MAINGAME_H
#define MAINGAME_H

#include <QWidget>

namespace Ui {
class mainGame;
}

class mainGame : public QWidget
{
    Q_OBJECT

public:
    explicit mainGame(QWidget *parent = nullptr);
    ~mainGame();

private:
    Ui::mainGame *ui;
};

#endif // MAINGAME_H
