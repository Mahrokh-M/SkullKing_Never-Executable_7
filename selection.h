#ifndef SELECTION_H
#define SELECTION_H

#include <QWidget>

namespace Ui {
class Selection;
}

class Selection : public QWidget
{
    Q_OBJECT

public:
    explicit Selection(QWidget *parent = nullptr);
    ~Selection();

private slots:

    void on_Server_clicked();

    void on_Client_clicked();

    void on_Exit_clicked();

private:
    Ui::Selection *ui;
};

#endif // SELECTION_H
