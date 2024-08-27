#include "mainwindow.h"

#include <QDebug>
#include <iostream>
#include <QFont>
#include <QObjectList>
#include <QPixmap>
#include <QScreen>
#include <QPainter>
//#include <QtPrintSupport/QPrinter>
//#include <QtPrintSupport/QPrintDialog>
#include <QFileDialog>
#include <QString>
#include <random>
#include <QStackedLayout>
#include <QSqlRecord>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    fPrep.setupUi(this);
    fRep.setupUi(this);
    setMinimumSize(640,480);
    model = new QSqlTableModel(this);
    qumodel = new QSqlTableModel(this);

    tableView = new QTableView(this);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->resizeColumnsToContents();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->horizontalHeader()->setStretchLastSection(true);
    //    tableView->setFixedSize(650,300);

    btn["record"] = (new QPushButton("Отчет по остаткам",this));
    btn["edit"] = (new QPushButton("Все таблицы"));
    btn["validS"] = (new QPushButton("Подтверждение передачи",this));
    btn["validO"] = (new QPushButton("Подтверждение приёма",this));
    btn["stock"] = (new QPushButton("Склад",this));

    btnEdit["back"] = (new QPushButton("Обратно",this));
    btnEdit["provider"] = (new QPushButton("Поставщики",this));
    btnEdit["client"] = (new QPushButton("Клиенты",this));
    btnEdit["ordered"] = (new QPushButton("История поставок",this));
    btnEdit["send"] = (new QPushButton("История отправок",this));
    btnEdit["stock"] = (new QPushButton("Склад",this));
    btnEdit["product"] = (new QPushButton("Товары",this));
    QHBoxLayout *hlay1 = new QHBoxLayout();
    QVBoxLayout *vlay2 = new QVBoxLayout();
    QVBoxLayout *bGroupML = new QVBoxLayout();
    QVBoxLayout *bGroupEL = new QVBoxLayout();
    QHBoxLayout *mainMenuLay = new QHBoxLayout();
    hlay1->addWidget(btnInsert);
    hlay1->addWidget(btnDelete);
    hlay1->addWidget(btnUpdate);
    hlay1->addSpacing(300);
    vlay2->addLayout(hlay1);
    vlay2->addWidget(tableView);
    for(auto &i:btn) {
        bGroupML ->addWidget(i.second);
    }
    for(auto &i:btnEdit) {
        bGroupEL ->addWidget(i.second);
    }
    bGroupM->setLayout(bGroupML);
    bGroupE->setLayout(bGroupEL);
    btnStack->addWidget(bGroupM);
    btnStack->addWidget(bGroupE);
    btnStack->setCurrentWidget(bGroupM);
    mainMenuLay->addWidget(btnStack);
    mainMenuLay->addLayout(vlay2);

//        for(int i=1; i < 21; i++) {
//            query.exec("insert into stock values("+QString::number(i)+","+QString::number(0)+")");
//        }
    //    QString bufItms[20] = { "Screwdriver", "Hammer", "Wrench", "Drill", "Saw", "Pliers", "Tape Measure", "Level", "Chisel", "Utility Knife", "Ladder", "Flashlight", "Safety Glasses", "Gloves", "Extension Cord", "Paint Brush", "Sandpaper", "Toolbox", "Nails", "Screws"
    //    };
    //    QString bufItmsDescr[20] = { "A tool used for turning screws.", "A tool with a heavy metal head used for breaking things and driving nails.", "A tool used for gripping and turning nuts and bolts.", "A power tool used for drilling holes.", "A tool for cutting wood and other materials.", "A hand tool used for gripping and bending objects.", "A measuring tool used to measure lengths.", "A tool used to check if a surface is level.", "A tool with a sharp edge for carving or cutting wood.", "A knife with a retractable blade used for various cutting tasks.", "A structure used for climbing to reach higher places.", "A portable light source.", "Protective eyewear to safeguard the eyes.", "Hand coverings used for protection and safety.", "A long, flexible electrical cable used to extend the reach of electrical devices.", "A brush used for applying paint.", "A material used for smoothing or polishing surfaces.", "A box used to store and organize tools.", "Metal fasteners used for joining materials together.", "Metal fasteners used for securing objects."
    //    };
    //    for(int i=1; i < 20; i++) {
    //        query.exec("insert into product values("+QString::number(1+i)+","+QString::number(rand()%5)+",\'"+bufItms[i]+"\',\'"+bufItmsDescr[i]+"\')");
    //    }
    int bufItPrices[20] = {150,300,250,2000,800,180,100,350,220,120,1500,400,100,80, 500,50, 30, 700,60, 70
                          };
    mainmen->setLayout(mainMenuLay);
    stackWid->addWidget(mainmen);
    stackWid->addWidget(fPrep.widget);
    stackWid->addWidget(fRep.centralwidget);
    setCentralWidget(stackWid);
    stackWid->setCurrentWidget(mainmen);
    btnStack->setMaximumWidth(200);
    //fPrep.radioButton_5->setText("ssss");
    //qobject_cast<QRadioButton*>(fPrep.widget->children().at(4))->setText("ssss");
    con.show();
    connect(con.ok, SIGNAL(clicked()), this, SLOT(prepare()));

    connect(btnInsert, SIGNAL(clicked()), this, SLOT(onAddButtonClickedSlot()));
    connect(btnUpdate, SIGNAL(clicked()), this, SLOT(onEditButtonClickedSlot()));
    connect(tableView, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onEditButtonClickedSlot()));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(deleteRowSlot()));
    connect(dialog.buttonSave, SIGNAL(clicked()), this, SLOT(onSaveButtonClickedSlot()));
    connect(fPrep.back,SIGNAL(clicked()),this,SLOT(backToMain()));
    connect(fRep.back,SIGNAL(clicked()),this,SLOT(backToMain()));
    connect(fPrep.go, SIGNAL(clicked()),this,SLOT(getReport()));
    connect(btn["record"], SIGNAL(clicked()),this,SLOT(toReport()));
    connect(btn["validS"], &QPushButton::clicked, this,[this]{tableCur="send";setupSQLTableModel( "send",   QStringList()
                  <<"Отправочный ID"<<"ID товара"<<"Количество"<<"Цена за каждый"<<"ID клиента" << "Дата отправки");trigger=1;});
    connect(btn["validO"], &QPushButton::clicked, this,[this]{tableCur="ordered";setupSQLTableModel( "ordered",   QStringList()
                <<"ID заказа"<<"ID товара"<<"Количество"<<"Цена за каждый"<< "Дата приёма");trigger=1;});
    connect(btn["stock"], &QPushButton::clicked, this,[this]{tableCur="stock";setupSQLTableModel( "stockview",   QStringList()
                                                                                     <<"ID товара"<<"Название"  << "Количество"  );});
    connect(btn["edit"], &QPushButton::clicked, this, [this]{swapButtons(1);});


    connect(btnEdit["back"], &QPushButton::clicked, this, [this]{swapButtons(0);});
    connect(btnEdit["provider"], &QPushButton::clicked, this,[this]{tableCur="provider";setupSQLTableModel( "provider",
                                          QStringList() <<"ID поставщика"<<"Название"<< "Телефонный номер");});
    connect(btnEdit["client"], &QPushButton::clicked, this,[this]{tableCur="client";setupSQLTableModel( "client",
          QStringList() <<"ID клиента"<<"Название"  << "Телефонный номер"  );});
    connect(btnEdit["ordered"], &QPushButton::clicked, this,[this]{tableCur="ordered";setupSQLTableModel( "ordered",   QStringList()
                <<"ID заказа"<<"ID товара"<<"Количество"<<"Цена за каждый"<< "Дата приёма");});
    connect(btnEdit["send"], &QPushButton::clicked, this,[this]{tableCur="send";setupSQLTableModel( "send",   QStringList()
                  <<"Отправочный ID"<<"ID товара"<<"Количество"<<"Цена за каждый"<<"ID клиента" << "Дата отправки");});
    connect(btnEdit["product"], &QPushButton::clicked, this,[this]{tableCur="product";setupSQLTableModel( "product",   QStringList()
                                                                                       <<"ID товара"<<"ID поставщика"<<"Название"<<"Описание");});
    connect(btnEdit["stock"], &QPushButton::clicked, this,[this]{tableCur="stock";setupSQLTableModel( "stock",   QStringList() <<"ID товара"  << "Количество"  );});

    connect(fPrep.ww, &QPushButton::clicked, this, [this]{datePlus="week";});
    connect(fPrep.mm, &QPushButton::clicked, this, [this]{datePlus="month";});
    connect(fPrep.yy, &QPushButton::clicked, this, [this]{datePlus="year";});
    //    QObjectList children = fPrep.widget->children();
    // QObjectList children = fPrep.widget->findChildren<QObject*>();
    //    for(QObject * child: children) {
    //        QWidget *childWidget = qobject_cast<QWidget*> (child);
    //        if (childWidget) {
    //            QFont font = childWidget->font();
    //            font.setPointSize(15);
    //            childWidget->setFont(font);
    //            connect(childWidget,SIGNAL(clicked()),this,SLOT(backToMain()));
    //        }
    //    }
    QSqlQuery query;
    query.exec("SELECT product.name, sum(ordered.amount) , b.ssum , sum(ordered.amount)-b.ssum "
               "    FROM  product, ordered,"
               "    (select prodid, sum(amount) as ssum from send group by prodid) AS b"
               "    WHERE product.id = ordered.prodid AND ordered.prodid = b.prodid AND"
               "    supdate between timestamptz \'"+fPrep.dateEdit->text()+"\' and timestamptz \'"+fPrep.dateEdit->text()+"\'+interval \'1 "+datePlus+"\'"
               "    GROUP BY product.name, b.ssum");
//    model->setQuery(query);

}
void MainWindow::prepare() {
    connectToDataBase();
//    setupSQLTableModel( "stock",   QStringList() <<"ID товара"  << "Количество"  );
    setupSQLTableModel( "stockview",   QStringList() <<"ID товара"<<"Название"  << "Количество"  );
    con.close();
    if (!db.open()) {
        QMessageBox::critical(0, "Ошибка ввода", "Не удалось подключиться к базе данных");
    }
    else {
        query = QSqlQuery(db);
        show();
    }
}

void MainWindow::swapButtons(bool gr) {
   if(gr) btnStack->setCurrentWidget(bGroupE);
   else {
       setupSQLTableModel( "stockview",   QStringList() <<"ID товара"<<"Название"  << "Количество"  );
       btnStack->setCurrentWidget(bGroupM);
   }
}
void MainWindow::getReport() {
    stackWid->setCurrentWidget(fRep.centralwidget);
    fRep.tableView->setModel(qumodel);
    qumodel->setQuery("SELECT product.name AS Товар, sum(ordered.amount) AS Приход, b.ssum AS Расход, sum(ordered.amount)-b.ssum AS Остаток"
               "    FROM  product, ordered,"
               "    (select prodid, sum(amount) as ssum from send group by prodid) AS b"
               "    WHERE product.id = ordered.prodid AND ordered.prodid = b.prodid AND"
               "    supdate between timestamptz \'"+fPrep.dateEdit->text()+"\' and timestamptz \'"+fPrep.dateEdit->text()+"\'+interval \'1 "+datePlus+"\'"
               "    GROUP BY product.name, b.ssum");

}

void MainWindow::toReport() {
    stackWid->setCurrentWidget(fPrep.widget);
}

void MainWindow::saveReport() {
    QSize bufSz = this->size();
    this->setFixedSize(210*3,305*3);
    QPixmap okno = QWidget::grab(QRect(QPoint(0,0),size()));
    this->setFixedSize(bufSz);
    QImage sShot = okno.toImage();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "otchet",
                                                    tr("Images (*.png)"));
    sShot.save(fileName, "PNG");
    //    QPrinter *printer = new QPrinter(); //печатает только маленький кусок
    //            QPrintDialog *dlg = new QPrintDialog(printer,0);
    //            if(dlg->exec() == QDialog::Accepted) {
    //                    QPainter *painter = new QPainter(printer);
    //                    painter->drawImage(QPoint(0,0),sShot);
    //                    painter->end();
    //            }
    //            delete dlg;
}

void MainWindow::backToMain() {
    stackWid->setCurrentWidget(mainmen);
    setupSQLTableModel( "stockview",   QStringList() <<"ID товара"<<"Название"  << "Количество"  );
}

void MainWindow::setupSQLTableModel(QString tableName,   QStringList headers) {
    trigger=0;
    colNums = tabList[tableCur].size();
    int j=0;
    for(;j<colNums;j++) {
        dialog.linedVec[j]->show();
        dialog.labVec[j]->show();
    }
    for(;j<7;j++) {
        dialog.linedVec[j]->hide();
        dialog.labVec[j]->hide();
    }
    model->setTable(tableName);

    for(int i = 0;  i < model->columnCount();  i++){
        model->setHeaderData( i,  Qt::Horizontal,  headers[i]);
    }
    model->setSort(0, Qt::AscendingOrder);
    tableView->setModel(model);
    model->select();
}


void MainWindow::onEditButtonClickedSlot()
{
    if(tableView->currentIndex().isValid()) {
        forEdit = true;
        dialog.buttonSave->setText("Сохранить");

        for(int i=0; i<colNums;i++) {
            dialog.labVec[i]->setText(tabList[tableCur][i]);
            dialog.linedVec[i]->setText(model->index(tableView->currentIndex().row(), i, QModelIndex()).data().toString());
        }
        dialog.show();

    }
}

void MainWindow::onAddButtonClickedSlot()
{
    forEdit = false;
    dialog.buttonSave->setText("Добавить строку");
    for(int i=0; i<colNums;i++) {
        dialog.labVec[i]->setText(tabList[tableCur][i]);
    }
    dialog.show();
    for(int i=0;i<7;i++) dialog.linedVec[i]->clear();

}

void MainWindow::onSaveButtonClickedSlot()
{
    if(forEdit) { updateRow(); }
    else insertRow();
}


void MainWindow::insertRow()
{
    QSqlQuery query;
    QString bufS="";
    for(int i=0;i<colNums-1;i++) {
        if(isStr[tableCur][i]) bufS += "\'"+dialog.linedVec[i]->text()+"\'";
        else bufS += dialog.linedVec[i]->text();
        bufS+=",";
    }
    if(isStr[tableCur][colNums-1]) bufS += "\'"+dialog.linedVec[colNums-1]->text()+"\'";
    else bufS += dialog.linedVec[colNums-1]->text();
    if(!query.exec( "INSERT INTO "  +tableCur+  " VALUES("+bufS+")")){
        QMessageBox::critical(0, "Не удалось добавить строку", query.lastError().text());
        qDebug()<<"INSERT INTO "  +tableCur+  " VALUES("+bufS+")\n";
    }
    else {
        if(trigger) {
            QString bufS2="";
            if (tableCur=="send") bufS2="-";
            else bufS2="+";
            bufS2+=dialog.linedVec[2]->text();
            QString bufS3=dialog.linedVec[1]->text();
            if(!query.exec( "UPDATE stock SET amount=amount"+bufS2+" WHERE prodid = " +bufS3+";")){
                QMessageBox::critical(0, "Не удалось изменить строку", query.lastError().text());
            }
        }
        model->select();
        dialog.close();
    }
}



void MainWindow::updateRow()
{
    QModelIndex ind = model->index(tableView->currentIndex().row(), 0, QModelIndex());
    QString str = ind.data().toString();
    QString bufS(""); QString bufS2(""); QString bufSStock(""); if(tableCur=="stock") bufSStock="prod";
    QSqlRecord record = db.record(tableCur);
    int n = record.count();
    for(int i = 0; i < n-1; i++) {
      if(isStr[tableCur][i]) bufS2="\'";
      else bufS2="";
      bufS+=  "\""+record.fieldName(i)+"\""+"="+bufS2+dialog.linedVec[i]->text()+bufS2+", ";
    }
    if(isStr[tableCur][n-1]) bufS2="\'";
    else bufS2="";
    bufS+=  record.fieldName(n-1)+"="+bufS2+dialog.linedVec[n-1]->text()+bufS2+" ";
    QSqlQuery query;

    if(!query.exec( "UPDATE "  +tableCur+ " SET "+bufS+" WHERE "+bufSStock+"id = " +str+";")){
        QMessageBox::critical(0, "Не удалось изменить строку", query.lastError().text());
    }
    else {
        model->select();
        dialog.close();
    }
}


void MainWindow::deleteRowSlot(){

    QModelIndex ind = model->index(tableView->currentIndex().row(), 0, QModelIndex());
    QString str = ind.data().toString();
    QString bufS("");
    if(tableCur == "stock") bufS = QString("prod");
    QSqlQuery query;
    if(!query.exec( "DELETE FROM "+tableCur+" WHERE "+bufS+"id = " +str+";"))
    {
        QMessageBox::critical(0, "Не удалось удалить строку", query.lastError().text());
    }
    model->select();
}

void MainWindow::connectToDataBase()
{
    db.driver();
//    db.setUserName("postgres");
//    db.setPassword("07172531");
//    db.setHostName("127.0.0.1");
//    db.setPort(5432);
    db.setUserName(con.userEd->text());
    db.setPassword(con.paswdEd->text());
    db.setHostName(con.hostEd->text());
    db.setPort(con.portEd->text().toInt());
    db.setDatabaseName(DB_NAME);

}

MainWindow::~MainWindow() {

}
