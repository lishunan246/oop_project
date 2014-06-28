#ifndef PEOPLE_H
#define PEOPLE_H
#include <QString>
class people
{
    int uid;
    QString username;
    QString type;
public:
    people();
    people(const int& uid,const QString& username,const QString& type);
};

class admin:public people
{

};

class student:public people
{
};
class teacher:public people
{
};


#endif // PEOPLE_H
