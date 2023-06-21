#ifndef FORGOTPASS_H
#define FORGOTPASS_H

#include <QWidget>

namespace Ui {
class ForgotPass;
}

class ForgotPass : public QWidget
{
    Q_OBJECT

public:
    explicit ForgotPass(QWidget *parent = nullptr);
    ~ForgotPass();

private:
    Ui::ForgotPass *ui;
};

#endif // FORGOTPASS_H
