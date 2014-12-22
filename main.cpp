#include "widget.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog* loginDialog = new LoginDialog();
    loginDialog->show();

    return a.exec();
}
