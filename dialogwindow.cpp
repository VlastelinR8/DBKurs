#include "dialogwindow.h"

DialogWindow::DialogWindow(QWidget *parent) : QWidget(parent)
{
        setMinimumSize(600,400);

        for(int i=0;i<7;i++) {
            labVec.push_back(new QLabel);
            linedVec.push_back(new QLineEdit);
        }

        buttonSave = new QPushButton("Сохранить",this);
        QPushButton *buttonCancel = new QPushButton("Отмена",this);

        QHBoxLayout *hlayout = new QHBoxLayout();
        hlayout->addSpacing(200);
        hlayout->addWidget(buttonSave);
        hlayout->addWidget(buttonCancel);
        QVBoxLayout *vlayout = new QVBoxLayout(this);
//        for(int i=0;i<3;i++) {
//            vlayout->addWidget(label[i]);
//            vlayout->addWidget(lineedit[i]);
//        }

        for(int i=0;i<6;i++) {
            vlayout->addWidget(labVec[i]);
            vlayout->addWidget(linedVec[i]);
            linedVec[i]->setText("dsfsdf");
        }
        vlayout->addLayout(hlayout);

      connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));

}
