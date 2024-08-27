#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QSpacerItem>
#include <vector>
using namespace std;
class DialogWindow : public QWidget
{
    Q_OBJECT
public:
//    vector<QLineEdit*> lineedit {vector<QLineEdit*>(7,new QLineEdit())}; это 7 ссылок на linedit, а не 7 объектов
//    vector<QLabel*> label {vector<QLabel*>(7, new QLabel())};
    explicit DialogWindow(QWidget *parent = nullptr);

    friend class MainWindow;             //  для доступа из MainWindow к закрытым полям

private:
    QPushButton *buttonSave;
    QLineEdit* lineedit1;
    QLineEdit* lineedit2;
    QLineEdit* lineedit3;
    vector<QLabel*> labVec;
    vector<QLineEdit*> linedVec;

};

#endif // DIALOGWINDOW_H
