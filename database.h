#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <people.h>
class database
{
    QSqlDatabase db;

    QSqlTableModel* model;
public:
    database()
    {

    }

    virtual ~database()
    {

        delete model;
    }

    bool connect();//连接数据库
    int checkPassword(const QString& username,const QString& password);
    bool newUser(const QString& username,const QString& password,const QString& type);
    bool delUser(const int& id);
    QString getTypeByUid(const int& id);
    QString getUsernameByUid(const int& uid);

    bool addLecture(
            const QString& lname,
            const QString& ltype,
            const QString& classroom,
            const int& tid,
            const float& credit,
            const int& day,
            const int& time
            );
    bool delLecture(const int& lid);
    bool addTake(const int& lid,const int& uid);
    bool delTake(const int& lid,const int& uid);

    QSqlTableModel* getLecureByType(const QString& type);
    QSqlTableModel* getStudentByLid(const int& lid);
    QSqlTableModel* getGradeByUid(const int& uid);
    //QSqlRecord getStudentByLid(const int& lid);

};

#endif // DATABASE_H
