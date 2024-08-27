#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent) { }

DataBase::~DataBase() {}
bool DataBase::inserIntoQualTable(const QVariantList  &data)                  //   метод вставки строки в таблицу qual_table ,  принимает QVariantList  т.к.  значения в таблицах могут быть разных типов.
{
    QSqlQuery query;

    query.prepare( "INSERT INTO "  TABLE1 " ( p00,  p01 ) "            //   готовим запрос
                                           "VALUES  (?,?)");
    query.addBindValue(data[0].toString());
    query.addBindValue(data[1].toString());

    if(!query.exec()){                                                                       //  выполняем запрос методом exec()
        qDebug() << "error insert into " << TABLE1;
        qDebug() << query.lastError().text();                                       //  в этом методе предусмотрен вывод информации об ошибках.
        return false;
    } else {
        return true;
    }
}

//void DataBase::closeDataBase()  {  db.close();  }
