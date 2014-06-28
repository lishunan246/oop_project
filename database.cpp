#include "database.h"
#include <QSqlTableModel>
#include <QTableView>

database::database()
{

}
bool database::connect()
{
    db=QSqlDatabase::addDatabase("QMYSQL","coonA");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("lishunan");
    db.setUserName("lishunan");
    db.setPassword("lishunanofzju");
    if(!db.open())
    {
        qDebug()<<db.lastError().text()<<endl;
        return false;
    }
    else
    {
        QString x="connect success";
        qDebug()<<x<<endl;
        return true;
    }
}

QString database::getTypeByUid(const int &id)
{
    QString a;
    a.setNum(id);
    QSqlTableModel model(0,db);
    model.setTable("people");
    model.setFilter(QString("uid=")+a);
    model.select();
    QString t;
    t=model.record(0).value("type").toString();
    qDebug()<<model.query().lastQuery();

    return t;

}
QString database::getUsernameByUid(const int &id)
{
    QString a;
    a.setNum(id);
    QSqlTableModel model(0,db);
    model.setTable("people");
    model.setFilter(QString("uid=")+a);
    model.select();
    QString t;
    t=model.record(0).value("username").toString();
    qDebug()<<model.query().lastQuery();

    return t;

}

int database::checkPassword(const QString &username, const QString &password)
{
    if(username==NULL)
        return false;
    qDebug()<<"u:"<<username<<endl;
    qDebug()<<"p:"<<password<<endl;

    QSqlTableModel model(0,db);
    model.setTable("people");
    model.setFilter("username='"+username+"'");
    model.select();

    QString t;
    t=model.record(0).value("password").toString();
    qDebug()<<"t:"<<t<<endl;
    qDebug()<<model.filter()<<model.rowCount()<<endl;
    qDebug()<<db.lastError().text()<<endl;

    QString a,b,c;
    a=model.record(0).value("uid").toString();
    b=model.record(0).value("username").toString();
    c=model.record(0).value("type").toString();
    if(t==password)
        return a.toInt();
    else
        return false;
}
 bool database::newUser(const QString &username, const QString &password,const QString& type)//向数据库中插入新用户
 {
    QSqlQuery query(db);
    query.prepare("INSERT INTO people (password, username, type) "
                       "VALUES (:password, :username, :type)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":type", type);
    bool i =query.exec();
    qDebug()<<db.isOpenError()<<endl;
    qDebug()<<db.isOpen()<<endl;
    qDebug()<<query.lastError().text()<<endl;
    return i;
 }

 bool database::delUser(const QString &username)
 {
     QSqlQuery query(db);
     query.prepare("DELETE FROM people WHERE username=\'"+username+"\'");

     bool i =query.exec();
     qDebug()<<db.isOpenError()<<endl;
     qDebug()<<db.isOpen()<<endl;
     qDebug()<<query.lastError().text()<<endl;
     return i;
 }