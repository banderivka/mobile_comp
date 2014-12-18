#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QSpacerItem>
#include <iostream>
#include <string>
#include <testClass.h>
#include <QLabel>
#include <QtSql>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:

    enum { NumGridRows = 2, NumButtons = 6, NumNavigationButtons = 4, MaxNumAnswers = 5};

    QGroupBox *_buttonsGroupBox;
    QPushButton *_testButtons[NumButtons * NumGridRows];
    QButtonGroup * _gTestButtons;

    QGroupBox *_navigationGroupBox;
    QPushButton *_navigationButtons[NumNavigationButtons];
    QButtonGroup * _gnavigationButtons;

    QGroupBox *_testGroupBox;
    QLabel *_question;
    QRadioButton *_rb[MaxNumAnswers];
    QButtonGroup * _grb;
    QPushButton *_calcelButton;

    Test *_tc;

    QPushButton *_acceptButton;
    QPushButton *_closeButton;
    QButtonGroup *_okCancel;
    QGroupBox *_okCancelGroupBox;

private:
    void createGroupBoxWithAnswerButtons();
    void createNavigationPanel();
    void createQuestionPanel();
    void createOkCancelPanel();

    void loadTestFromXML(const char *);
    void repaintGroupBoxWithActiveQuestion(int);

    void connectToDB();

private slots:
    void handleNavigationButton(int);
    void handleTestButtons(int);
    void handleRadioButtons(int);
    void handleCancelButton();
    void handleAcceptButton();

signals:
    void numberOfQuestionChanged(int newValue);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
