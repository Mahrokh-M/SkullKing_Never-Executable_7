#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "history.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_pushButton_edit_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_history_clicked();

private:
    Ui::MainMenu *ui;
};
#endif // MAINMENU_H
