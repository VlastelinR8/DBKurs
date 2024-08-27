#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define DB_NAME   "wareg"
#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include <map>
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include "dialogwindow.h"
#include "connect.h"
#include <vector>
#include <QStackedWidget>
#include <QStringList>
#include <QSqlQueryModel>
#include "ui_mainwindow.h"
#include "ui_form.h"
#include "ui_report.h"
using namespace std;
//using boost::any;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    unordered_map<string, QPushButton*> btn;
    unordered_map<string, QPushButton*> btnEdit;
    QPushButton *btnInsert = new QPushButton("Добавить", this);
    QPushButton *btnDelete = new QPushButton("Удалить",this);
    QPushButton *btnUpdate = new QPushButton("Редактировать",this);
    Ui::form fPrep;
    Ui::report fRep;
    QWidget *mainmen = new QWidget;
    QStackedWidget *stackWid = new QStackedWidget();
    QStackedWidget *btnStack = new QStackedWidget();
    QWidget *bGroupM = new QWidget();
    QWidget *bGroupE = new QWidget();
    QSqlQuery query;
    QString tableCur = "stock";
    QString datePlus = "week";
    int colNums;
    ConnectW con;
    map<QString, vector<QString>> tabList = {
        {"stock", vector<QString>{"ID товара", "Количество"}},
        {"provider", vector<QString>{"ID поставщика", "Название", "Телефонный номер"}},
        {"client", vector<QString>{"ID клиента", "Название", "Телефонный номер"}},
        {"product", vector<QString>{"ID товара", "ID поставщика", "Название", "Описание"}},
        {"send", vector<QString>{"Отправочный ID", "ID товара", "Количество", "Цена за каждый", "ID клиента", "Дата отправки"}},
        {"ordered", vector<QString>{"ID заказа", "ID товара", "Количество", "Цена за каждый", "Дата приёма"}}
    };
    map<QString, vector<bool>> isStr = {
        {"stock", vector<bool>{0, 0}},
        {"provider", vector<bool>{0, 1, 1}},
        {"client", vector<bool>{0, 1, 1}},
        {"product", vector<bool>{0, 0, 1, 1}},
        {"send", vector<bool>{0, 0, 0, 0, 0, 1}},
        {"ordered", vector<bool>{0, 0, 0, 0, 1}}
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

 private:
                  //  объект нашего класса для бд
    QTableView *tableView;         //  обычный вид  QTableView
    QSqlTableModel  *model;
    QSqlQueryModel *qumodel;//   модель  QSqlTableModel
    DialogWindow dialog;
    void setupSQLTableModel(QString tableName,   QStringList headers);        //  методы настройки  SQLTableModel   и  TableView
    void connectToDataBase();
    void insertRow();              //  методы добавления и изменения строк в БД
    void updateRow();
    bool forEdit = false;
    bool trigger =0;



private slots:
    void deleteRowSlot();
    void onEditButtonClickedSlot();
    void onAddButtonClickedSlot();
    void onSaveButtonClickedSlot();
    void backToMain();
    void toReport();
    void getReport();
    void saveReport();
    void prepare();
    void swapButtons(bool gr);
};

#endif    // MAINWINDOW_H
