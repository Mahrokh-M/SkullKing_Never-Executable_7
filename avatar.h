#ifndef AVATAR_H
#define AVATAR_H

#include <QWidget>

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

private:
    Ui::Avatar *ui;
};

#endif // AVATAR_H
