#ifndef CONNNECT_H
#define CONNNECT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStringList>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlTableModel>
#include <QSqlRecord>

#ifdef Q_OS_WIN
#pragma execution_character_set("UTF-8")    // 解决中文乱码
#endif

QString genItem(
        const QString order,
        const QString operator_id,
        const QString type,
        const float wire_d,
        const float distance,
        const float rate,
        const float range,
        const int target_production,
        const int actual_production,
        const int NG_amount,
        const float NG_rate) {
    // 将输入转化为SQL指令
    QString item = QString("replace into %1 values ("
                               "'%2', "
                               "'%3', "
                               "'%4', "
                               "%5, "
                               "%6, "
                               "%7, "
                               "%8, "
                               "%9, "
                               "%10, "
                               "%11, "
                               "%12)")
            .arg("OrderInfo").arg(order).arg(operator_id).arg(type)
            .arg(wire_d).arg(distance).arg(rate).arg(range)
            .arg(target_production).arg(actual_production).arg(NG_amount).arg(NG_rate);

    return item;
}


static bool createConnection() {

//    qDebug()<<"可以使用的数据库";
//       QStringList drivers=QSqlDatabase::drivers();
//       foreach(QString driver,drivers)
//           qDebug()<<driver;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    // db.exec("SET NAMES 'UTF-8'");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("680414Chen");
    db.open(); // 想要创建表需要先open

    // db.exec("CREATE DATABASE IF NOT EXISTS test_pylon");
    db.setDatabaseName("test_pylon");

    if (!db.open()) {
        qDebug()<< db.lastError();
        qDebug()<<"Unable to open database";
        return false;
    }
    else {
        // float a = 1.2;
        // QString str = QString("ME, %1, %2, %3, %4, %5, %6, %7, %8").arg("Cool").arg(a).arg(a).arg(a);
        // qDebug()<< str;
        qDebug()<<"Database connection established";
    }
    // 如果MySQL数据库中已经存在同名的表，那么下面的代码不会执行

    QSqlQuery query(db);
    // 创建 course 表
    //query.exec("create table course5 (name varchar(20) primary key, teacher varchar(20))");
    // query.exec("insert into course3 values(0, '数学', '刘老师')");
    // query.exec("insert into course3 values(10, '英语', '张老师')");
    //query.exec("insert into course5 values ('计算机', '李老师2')");

    QString item =  genItem("t20210601-1",
                            "AA054",
                            "镀银铜带",
                            2.19,
                            1.2,
                            0.5,
                            0.02,
                            213,
                            200,
                            10,
                            0.02);
    // query.exec(item);

    query.exec("select * from t20210602");
    // query.exec("select 生产单号 from orderinfo");
    qDebug() << query.record().count();
    while (query.next())
    {
         // qDebug() << query.value(0).toInt() << query.value(1).toString()<< query.value(2).toString();
         qDebug() << query.value(2).toString();
    }

    db.close();

    return true;
}

#endif // CONNNECT_H
