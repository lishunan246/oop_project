#include "loginwindow.h"
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
    QHBoxLayout* btnLayout=new QHBoxLayout;
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
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


}
LoginWindow::~LoginWindow()
{



}
void LoginWindow::accept()
{


    QXmlQuery query;
}

/*
void LoginWindow::accept()
{
    QString a=usrLineEdit->text().trimmed();
    QString b=pwdLineEdit->text().trimmed();

    QMessageBox::warning(this,a,b,QMessageBox::Yes);

}*/
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
