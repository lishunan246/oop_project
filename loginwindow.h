#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QDialog>

class QLineEdit;

class LoginWindow:public QDialog
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
public slots:
    virtual void accept();
private:
    QLineEdit* usrLineEdit;
    QLineEdit* pwdLineEdit;

};

#endif // LOGINWINDOW_H
