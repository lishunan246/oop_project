#include "mainwindow.h"
#include <QApplication>
#include "loginwindow.h"
#include "database.h"
#include <QMessageBox>

database db;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    if(!db.connect())
    {
        QMessageBox::warning(0,"Error","Unable to open the database",QMessageBox::Yes);
    }
    else
    {
        w.show();
    }

    return a.exec();
}
