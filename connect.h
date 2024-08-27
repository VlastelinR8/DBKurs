#ifndef CONNECT_H
#define CONNECT_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
using namespace std;
class ConnectW : public QWidget
{
    Q_OBJECT

private:
    QLineEdit* userEd;
    QLineEdit* paswdEd;
    QLineEdit* hostEd;
    QLineEdit* portEd;
    QPushButton *ok = new QPushButton("OK", this);

public:
   explicit ConnectW() : QWidget() {
        QLabel *userL = new QLabel("Имя пользователя",this);
        QLabel *paswdL= new QLabel("Пароль",this);
        QLabel *hostL = new QLabel("IP сервера",this);
        QLabel *portL = new QLabel("Порт",this);
        userEd = new QLineEdit("postgres",this);
        paswdEd = new QLineEdit(this);
        paswdEd->setEchoMode(QLineEdit::Password);
        hostEd = new QLineEdit("127.0.0.1");
        portEd = new QLineEdit("5432");
        QVBoxLayout *vlayout = new QVBoxLayout(this);
        vlayout->addWidget(userL);
        vlayout->addWidget(userEd);
        vlayout->addWidget(paswdL);
        vlayout->addWidget(paswdEd);
        vlayout->addWidget(hostL);
        vlayout->addWidget(hostEd);
        vlayout->addWidget(portL);
        vlayout->addWidget(portEd);
        vlayout->addWidget(ok);
        setMinimumSize(400,200);
    }
    friend class MainWindow;

};
#endif // CONNECT_H
