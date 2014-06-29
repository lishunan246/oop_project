#include "database.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQuery>


bool database::connect()
{
    db=QSqlDatabase::addDatabase("QMYSQL");
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
/*
QSqlRecord database::getStudentByLid(const int &lid)
{
    QString id;
    id.setNum(lid);
    QSqlQuery a;

    a.exec("SELECT * FROM `take` natural join`people` WHERE lid="+id);

    return a.record();
}
*/
QSqlTableModel* database::getStudentByLid(const int& lid)
{
    QString id;
    id.setNum(lid);
    QSqlRelationalTableModel* rmodel=new QSqlRelationalTableModel(0,db);
    rmodel->setTable("take");
    rmodel->setRelation(2,QSqlRelation("people","uid","username"));
    //rmodel->setRelation(1,QSqlRelation("lecture","lid","lname"));
    rmodel->setFilter("lid="+id);
    rmodel->select();
    model=rmodel;
    return model;
}
 QSqlTableModel* database::getGradeByUid(const int& uid)
 {
     QString id;
     id.setNum(uid);
     QSqlRelationalTableModel* rmodel=new QSqlRelationalTableModel(0,db);
     rmodel->setTable("take");
     //rmodel->setRelation(2,QSqlRelation("people","uid","username"));
     rmodel->setRelation(1,QSqlRelation("lecture","lid","lname"));
     //rmodel->setFilter("grade is not null");
     rmodel->setFilter("grade is not null and uid="+id);
     rmodel->select();
     model=rmodel;
     return model;
 }
bool database::addTake(const int& lid,const int& uid)
{
    QSqlQuery q(db);
    QString l,u;
    l.setNum(lid);
    u.setNum(uid);
    q.exec("SELECT * from take where lid="+l+" and uid ="+u);
    //qDebug()<<q.record().value(<<endl;
    if(q.next())
        return false;
    QSqlQuery query(db);
    query.prepare("INSERT INTO take (lid, uid) "
                       "VALUES (:lid, :uid)");
    query.bindValue(":lid", lid);
    query.bindValue(":uid", uid);

    bool i =query.exec();

    qDebug()<<query.lastError().text()<<endl;
    return i;
}

bool database::delTake(const int& lid,const int& uid)
{
    QString l,u;
    l.setNum(lid);
    u.setNum(uid);
    QSqlQuery query(db);
    query.prepare("DELETE FROM take WHERE uid= "+u+" and lid= "+l);

    bool i =query.exec();
    qDebug()<<db.isOpenError()<<endl;
    qDebug()<<db.isOpen()<<endl;
    qDebug()<<query.lastError().text()<<endl;
    return i;
}
bool database::setGrade(const int& lid,const int& uid,const int& grade)
{
    QString l,u,g;
    l.setNum(lid);
    u.setNum(uid);
    g.setNum(grade);

    QSqlQuery query(db);
    query.prepare("UPDATE take set grade = "+g+" where lid ="+l+" and uid ="+u);
    bool i =query.exec();
    qDebug()<<db.isOpenError()<<endl;
    qDebug()<<query.lastQuery()<<endl;
    qDebug()<<query.lastError().text()<<endl;
    return i;

}
QSqlTableModel* database::getScheduleOfTeacher(const int& uid)
{
    if(getTypeByUid(uid)!="teacher")
        return NULL;
    QString u;
    u.setNum(uid);
    model=new QSqlTableModel(0,db);
    model->setTable("lecture");
    model->setFilter("tid="+u);
    model->select();
    qDebug()<<model->query().lastQuery()<<model->record(0).value("lid");
    return model;
}
QSqlQueryModel *database::getScheduleOfStudent(const int& uid)
{
    if(getTypeByUid(uid)!="student")
        return NULL;
    QString u;
    u.setNum(uid);
    QSqlQueryModel* qmodel=new QSqlQueryModel(0);
    qmodel->setQuery(QSqlQuery("SELECT lname,lid,day,time,classroom FROM `take` natural join lecture natural join people WHERE uid="+u));
    qDebug()<<qmodel->query().lastQuery()<<qmodel->record(0).value("lid");
    return qmodel;
}
