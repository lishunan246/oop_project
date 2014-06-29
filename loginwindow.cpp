#include "loginwindow.h"
#include <database.h>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QtXmlPatterns/qxmlquery.h>
#include <QtXmlPatterns/QXmlResultItems>
#include <QtXmlPatterns/QXmlNodeModelIndex>
#include <QtXml>
#include <QtXmlPatterns/QXmlItem>
#include <QtSql>
#include <QTableView>

extern database db;

LoginWindow::LoginWindow(QWidget *parent):QDialog(parent)
{
    QLabel* usrLabel=new QLabel(tr("用户名"));
    QLabel* pwdLabel=new QLabel(tr("密码"));
    usrLineEdit=new QLineEdit;
    pwdLineEdit=new QLineEdit;
    pwdLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    QGridLayout* grid=new QGridLayout;
    grid->addWidget(usrLabel,0,0,1,1);
    grid->addWidget(usrLineEdit,0,1,1,3);
    grid->addWidget(pwdLabel,1,0,1,1);
    grid->addWidget(pwdLineEdit,1,1,1,3);

    QPushButton* okBtn=new QPushButton(tr("确定"));
    QPushButton* cancelBtn=new QPushButton(tr("取消"));
    QPushButton* addPeopleBtn=new QPushButton(tr("添加人员"));
    QPushButton* delPeopleBtn=new QPushButton(tr("删除人员"));
    QHBoxLayout* btnLayout=new QHBoxLayout;
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(addPeopleBtn);
    btnLayout->addWidget(delPeopleBtn);
    btnLayout->setSpacing(60);
    QVBoxLayout* windowLayout =new QVBoxLayout;

    windowLayout->addLayout(grid);
    windowLayout->addLayout(btnLayout);
    windowLayout->setMargin(40);
    windowLayout->addStretch(40);
    setLayout(windowLayout);

    setWindowTitle(tr("登录"));
    resize(300,150);

    connect(okBtn,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(reject()));
    connect(addPeopleBtn,SIGNAL(clicked()),this,SLOT(addPeople()));
    connect(delPeopleBtn,SIGNAL(clicked()),this,SLOT(delPeople()));


}

void LoginWindow::delPeople()
{
    //db.setGrade(2,1,30);
    QSqlQueryModel* a;
    a=db.getScheduleOfStudent(5);

    QTableView* b=new QTableView;
    b->setModel(a);
    b->show();
    qDebug()<<"lid:"<<a->record(0).value("lid")<<endl;

}

void LoginWindow::addPeople()
{
    QString username=usrLineEdit->text().trimmed();
    QString password=pwdLineEdit->text().trimmed();

    if(!db.newUser(username,password,"student"))
    {
        QMessageBox::warning(this,"Error","Unable to addPeople",QMessageBox::Yes);
    }
    else
    {

        QMessageBox::information(this,"Success","add successful",QMessageBox::Yes);
    }

}

/*void LoginWindow::accept()
{
    QFile xq("myquery.xq");
       QString fileName("the filename");
       QString publisherName("the publisher");
       qlonglong year = 1234;

       QXmlQuery query;

       query.bindVariable("file", QVariant(fileName));
       query.bindVariable("publisher", QVariant(publisherName));
       query.bindVariable("year", QVariant(year));

       query.setQuery(&xq, QUrl::fromLocalFile(xq.fileName()));

       QXmlResultItems result;
       query.evaluateTo(&result);
       QXmlItem item(result.next());
       while (!item.isNull()) {
           if (item.isAtomicValue()) {
               QVariant v = item.toAtomicValue();
               switch (v.type()) {
                   case QVariant::LongLong:
                       // xs:integer
                       break;
                   case QVariant::String:
                       // xs:string
                       break;
                   default:
                       // error
                       break;
               }
           }
           else if (item.isNode()) {
   #ifdef qdoc
               QXmlNodeModelIndex i = item.toNodeModelIndex();
               // process node
   #endif // qdoc
           }
           item = result.next();
       }

}
*/

void LoginWindow::accept()
{
    QString username=usrLineEdit->text().trimmed();
    QString password=pwdLineEdit->text().trimmed();

    int id=db.checkPassword(username,password);

    if(!id)
    {
        QMessageBox::warning(this,"Error","Unable to login",QMessageBox::Yes);
    }
    else
    {
        QString a,b;
        a=db.getTypeByUid(id);
        b=db.getUsernameByUid(id);
        qDebug()<<"type:"<<a<<endl;

        QMessageBox::information(this,a,b,QMessageBox::Yes);
    }

}
/*
void LoginWindow::accept()
{
    QString a=usrLineEdit->text().trimmed();
    QString b=pwdLineEdit->text().trimmed();
    QDomDocument doc("user");
    QFile file("user.xml");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QMessageBox::warning(this,"Error","Unable to open user.xml",QMessageBox::Yes);
    }
    QDomElement root = doc.createElement("users");
    doc.appendChild(root);

    QDomElement user = doc.createElement("user");
    root.appendChild(user);

    QDomElement username = doc.createElement("username");
    user.appendChild(username);

    QDomText t = doc.createTextNode(a);
    username.appendChild(t);

    QDomElement password = doc.createElement("password");
    user.appendChild(password);

    t = doc.createTextNode(b);
    password.appendChild(t);

    QString xml = doc.toString();

    QTextStream out(&file);
    out<<xml;

}
*/
