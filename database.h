#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <people.h>
class database
{
    QSqlDatabase db;
public:
    database();
    bool connect();//连接数据库
    int checkPassword(const QString& username,const QString& password);
    bool newUser(const QString& username,const QString& password,const QString& type);
    bool delUser(const QString& username);
    QString getTypeByUid(const int& id);
    QString getUsernameByUid(const int& uid);
};

#endif // DATABASE_H