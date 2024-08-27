#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>


#define TABLE1      "qual_table"           //  наши таблицы.    main_table  будет зависить от qual_table.
#define TABLE2      "main_table"



class DataBase : public QObject
{
    Q_OBJECT
public:
    DataBase(QObject *parent = 0);

    bool inserIntoQualTable(const QVariantList &data);
    ~DataBase();

private:
                       // Сам объект базы данных
    void closeDataBase();               //  закрыть бд
};

#endif   // DATABASE_H
