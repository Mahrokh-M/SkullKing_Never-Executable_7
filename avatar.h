#ifndef AVATAR_H
#define AVATAR_H

#include <QWidget>
extern int ChosenAvatar;
namespace Ui {
class Avatar;
}

class Avatar : public QWidget
{
    Q_OBJECT

public:
    explicit Avatar(QWidget *parent = nullptr);
    ~Avatar();

private slots:
    void on_pushButton_clicked();

    void on_Avatar1_clicked();

    void on_Avatar2_clicked();

    void on_Avatar3_clicked();

    void on_Avatar4_clicked();

private:
    Ui::Avatar *ui;
};

#endif // AVATAR_H
