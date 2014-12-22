#include <fstream>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QStringList>
#include <QDebug>
#include "widget.h"

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

class LoginDialog : public QDialog
{
    Q_OBJECT

private:
    Widget* w;

    QLabel* labelUsername;
    QLabel* labelPassword;
    QLabel* labelInfo;

    QLineEdit* editUsername;
    QLineEdit* editPassword;

    QDialogButtonBox* buttons;

    void setUpGUI();

public:
    explicit LoginDialog(QWidget *parent = 0);

    void setUsername( std::string& username );

    void setPassword( std::string& password );

public slots:

    void slotAcceptLogin();

};

#endif // LOGINDIALOG_H
