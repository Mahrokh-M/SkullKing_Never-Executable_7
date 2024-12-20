#include "history.h"
#include "ui_history.h"
#include <globals.h>
#include<QPushButton>
#include "mainmenu.h"
History::History(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
    // Create a QVBoxLayout for the main widget
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    // Create a QScrollArea
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    // Create a QWidget that will contain dynamically added buttons
    QWidget *buttonsWidget = new QWidget();
    scrollArea->setWidget(buttonsWidget);
//    QLabel *label = new QLabel;
//    label->setStyleSheet("border-image: url(:/new/prefix1/First_history_page.jpg);");
    buttonsWidget->setStyleSheet("QWidget {"
                          "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #FAD0C4, stop:1 #FFA07A);"
                          "}");

    // Create a QVBoxLayout for the QWidget
    QVBoxLayout *buttonsLayout = new QVBoxLayout(buttonsWidget);
    // Add the QScrollArea to your main widget or layout
    main_layout->addWidget(scrollArea);
    ui->pushButton_Back->raise();
    ui->pushButton_Back->setStyleSheet("QPushButton {background-color: #FFA07A; border: 2px solid #FAD0C4; border-radius: 5px; color: white;} QPushButton:hover {background-color: #FF8C66; }");


    QVector<Game_history>::Iterator it=Person->set_get_History().begin();
    for(int i=0, j=10; i<Person->set_get_History().size(); i++, j+=35){ //j specifies the distance of each button from top
        QString button_name=it->set_get_game_id();
        // Create a new push button
        QPushButton *button = new QPushButton(button_name, this);
        button->setStyleSheet("QPushButton {background-color: #FFA07A; border: 2px solid #FAD0C4; border-radius: 5px; color: white;} QPushButton:hover {background-color: #FF8C66; }");

        button->setGeometry(10, j, 300, 30);
        // Connect the button's clicked() signal to a slot
        connect(button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
        it++;
        buttonsLayout->addWidget(button);
    }
}

History::~History()
{
    delete ui;
}
Game_history::Game_history() {
    opponent_username = "";
    user_score = "";
    opponent_score = "";
    result="";
    game_id="";
    screenshot_path="";
}
Game_history::Game_history(QString opponent_username, QString opponent_score, QString user_score, QString result, QString game_id) {
    this->opponent_username = opponent_username;
    this->opponent_score = opponent_score;
    this->user_score = user_score;
    this->result=result;
    this->game_id=game_id;
}
QString& Game_history::set_get_opponent_username() {
    return opponent_username;
}
QString& Game_history::set_get_opponent_score() {
    return opponent_score;
}
QString& Game_history::set_get_user_score() {
    return user_score;
}
QString& Game_history::set_get_result() {
    return result;
}
QString& Game_history::set_get_game_id() {
    return game_id;
}
QString& Game_history::set_get_screenshot_path(){
    return screenshot_path;
}
void History::onButtonClicked() //All these pushbuttons have same slot, that gets the id of the selected game and then open the related ui
{
    // Get the button that was clicked
   QPushButton *clicked_button = qobject_cast<QPushButton *>(sender()); //sender() function returns a pointer to the object that sent the signal that triggered the current slot

    if (clicked_button) {
        // Get the text on the button
        QString clicked_buttonText = clicked_button->text(); //We need to understand which button was clicked to access the information of right gmae in the vector
        chosen_game_id=clicked_buttonText;
        this->close();
        Each_game_history* a=new Each_game_history;
        a->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        a->show();
    }
}

void History::on_pushButton_Back_clicked()
{
    this->close();
    MainMenu *main_page=new MainMenu();
    main_page->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    main_page->show();
}

