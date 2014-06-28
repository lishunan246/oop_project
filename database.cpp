#include "database.h"
#include <QSqlTableModel>
#include <QTableView>


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

 bool database::delUser(const int &id)
 {
     QString str;
     str.setNum(id);
     QSqlQuery query(db);
     query.prepare("DELETE FROM people WHERE uid="+str);

     bool i =query.exec();
     qDebug()<<db.isOpenError()<<endl;
     qDebug()<<db.isOpen()<<endl;
     qDebug()<<query.lastError().text()<<endl;
     return i;
 }

 bool database::addLecture(const QString &lname, const QString &ltype, const QString &classroom, const int &tid, const float &credit, const int &day, const int &time)
 {
     QSqlQuery query(db);
     query.prepare("INSERT INTO lecture (ltype, classroom, lname,tid,credit,day,time) "
                        "VALUES (:ltype, :classroom, :lname,:tid,:credit,:day,:time)");
     query.bindValue(":lname", lname);
     query.bindValue(":ltype", ltype);
     query.bindValue(":classroom", classroom);
     query.bindValue(":day",day);
     query.bindValue(":time",time);
     query.bindValue(":credit",credit);
     query.bindValue(":tid",tid);
     bool i =query.exec();
     qDebug()<<db.isOpenError()<<endl;
     qDebug()<<db.isOpen()<<endl;
     qDebug()<<query.lastError().text()<<endl;
     return i;
 }
bool database::delLecture(const int &lid)
{
    QString str;
    str.setNum(lid);
    QSqlQuery query(db);
    query.prepare("DELETE FROM lecture WHERE lid="+str);

    bool i =query.exec();

    qDebug()<<query.lastError().text()<<endl;
    return i;
}
QSqlTableModel *database::getLecureByType(const QString &type)
{

    model=new QSqlTableModel(0,db);
    model->setTable("lecture");
    model->setFilter("ltype='"+type+"'");
    model->select();
    qDebug()<<model->query().lastQuery()<<model->record(0).value("lid");
    return model;




}
