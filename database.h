#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
class database
{
    QSqlDatabase db;
public:
    database();
    bool connect();//连接数据库
    bool checkPassword(const QString& username,const QString& password);
    bool newUser(const QString& username,const QString& password,const QString& type);
    bool delUser(const QString& username);
};

#endif // DATABASE_H
