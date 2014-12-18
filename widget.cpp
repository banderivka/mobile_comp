#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //connectToDB();
    createGroupBoxWithAnswerButtons();
    createNavigationPanel();
    createQuestionPanel();
    createOkCancelPanel();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(_buttonsGroupBox);
    mainLayout->addWidget(_navigationGroupBox);
    mainLayout->addWidget(_testGroupBox);
    mainLayout->addWidget(_okCancelGroupBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Тестування"));

    connect(_gnavigationButtons, SIGNAL(buttonPressed(int)), this, SLOT(handleNavigationButton(int)));
    connect(_gTestButtons, SIGNAL(buttonClicked(int)), this, SLOT(handleTestButtons(int)));
    connect(_grb, SIGNAL(buttonClicked(int)), this, SLOT(handleRadioButtons(int)));
    connect(_closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(_calcelButton, SIGNAL(clicked()), this, SLOT(handleCancelButton()));
    connect(_acceptButton, SIGNAL(clicked()), this, SLOT(handleAcceptButton()));
}

void Widget::createGroupBoxWithAnswerButtons()
{
    _buttonsGroupBox = new QGroupBox;
    _gTestButtons = new QButtonGroup;

    QHBoxLayout *hlayout[NumGridRows];
    for (int i = 0; i < NumGridRows; ++i)
        hlayout[i] = new QHBoxLayout;

    QVBoxLayout *vlayout = new QVBoxLayout;

    for (int j = 0; j < NumGridRows; ++j)
    {
        //hlayout[j]->addStretch();
        for (int i = 0; i < NumButtons; ++i)
        {
            int k = i + j*NumButtons;
            _testButtons[k] = new QPushButton(tr("Питання %1").arg(i + j*NumButtons + 1));
            _testButtons[k]->setMaximumWidth(120);
            _gTestButtons->addButton(_testButtons[k], k);
             hlayout[j]->addWidget(_testButtons[k]);
        }
        //hlayout[j]->addStretch();
        vlayout->addLayout(hlayout[j]);
    }

    _buttonsGroupBox->setLayout(vlayout);
    _buttonsGroupBox->setFixedHeight(80);
}

void Widget::createNavigationPanel()
{
    _navigationGroupBox = new QGroupBox;
    _gnavigationButtons = new QButtonGroup;

    QHBoxLayout *hlayout = new QHBoxLayout;

    const char *navigationButtonNames[] = {"Початок", " < Попереднє", "Наступне > ", "Кінець"};

    hlayout->addStretch();
    for (int i = 0; i < NumNavigationButtons; ++i)
    {
        _navigationButtons[i] = new QPushButton(navigationButtonNames[i]);
        _navigationButtons[i]->setMaximumWidth(120);
        _gnavigationButtons->addButton(_navigationButtons[i], i);
        hlayout->addWidget(_navigationButtons[i]);
        if (i == 1) hlayout->addStretch();
    }
    hlayout->addStretch();

    _gnavigationButtons->setExclusive(true);
    _navigationGroupBox->setLayout(hlayout);
    _navigationGroupBox->setFixedHeight(60);

}

void Widget::createQuestionPanel()
{
    loadTestFromXML(":/files/test.xml");
    _tc->setActiveQuestion(0);
    Question qc = _tc->getActiveQuestion();

    _testGroupBox = new QGroupBox();
    _testGroupBox->setStyleSheet("QGroupBox { font-size: 19px; }");
                                // "font-weight: bold; }");
    _testGroupBox->setTitle(tr("Питання 1"));
    QVBoxLayout *vlayout = new QVBoxLayout;
    _question = new QLabel(QString::fromLocal8Bit(qc.getQuestion().c_str()));
    _question->setStyleSheet("QLabel { color : rgb( 0, 0, 171); font-size : 15px }");
    _calcelButton = new QPushButton(tr("Скасувати вибір"));
    _calcelButton->setMaximumWidth(150);

    vlayout->addWidget(_question);
    vlayout->addStretch();
    _grb = new QButtonGroup();

    size_t count = qc.getAnwsers(0).size();

    if (count > MaxNumAnswers)
    {
        qDebug() << tr("Too many answers!");
        return;
    }
    else if (count <=0)
    {
        qDebug() << tr("there are no answers!");
        return;
    }

    for (size_t i = 0; i < MaxNumAnswers; ++i)
    {
        if (i < count)
            _rb[i] = new QRadioButton(QString::fromLocal8Bit(qc.getAnwsers(0).at(i).c_str()));
        else
        {
            _rb[i] = new QRadioButton();
            _rb[i]->setVisible(false);
        }
        _rb[i]->setStyleSheet("QRadioButton { font-size : 15px }");
        _grb->addButton(_rb[i], i);
        vlayout->addWidget(_rb[i]);
    }
    vlayout->addWidget(_calcelButton);
    _testGroupBox->setLayout(vlayout);
}

void Widget::createOkCancelPanel()
{
     _okCancelGroupBox = new QGroupBox;
     _okCancel = new QButtonGroup();
     _acceptButton = new QPushButton(tr("Зберегти"));
     _closeButton = new QPushButton(tr("Закрити"));

     _okCancel->addButton(_acceptButton, 0);
     _okCancel->addButton(_closeButton, 1);
     QHBoxLayout *hlayout = new QHBoxLayout;

     hlayout->addStretch();
     hlayout->addWidget(_acceptButton);
     hlayout->addWidget(_closeButton);

     _okCancelGroupBox->setLayout(hlayout);

}

void Widget::loadTestFromXML(const char * filename)
{
    QDomDocument domDoc;
    _tc = new Test();
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly))
    {
        if(domDoc.setContent(&file))
        {
            QDomElement domElement= domDoc.documentElement();
            _tc->loadQuestionsFromXml(domElement);
        }
        file.close();
    }
    _tc->printTestResults();
}

void Widget::repaintGroupBoxWithActiveQuestion(int number)
{
    Question qc = _tc->getActiveQuestion();

    _testGroupBox->setTitle(tr("Питання ") + QString::number(number + 1));// + QString::number(number));

    _question->setText(QString::fromLocal8Bit(qc.getQuestion().c_str()));

    size_t count = qc.getAnwsers(0).size();

    if (count > MaxNumAnswers)
    {
        qDebug() << tr("Too many answers!");
        return;
    }
    else if (count <=0)
    {
        qDebug() << tr("there are no answers!");
        return;
    }

    _grb->setExclusive(false);
    for (size_t i = 0; i < MaxNumAnswers; ++i)
    {
        if (i < count)
        {
            _rb[i]->setText(QString::fromLocal8Bit(qc.getAnwsers(0).at(i).c_str()));
            _rb[i]->setVisible(true);
        }
        else
        {
            _rb[i]->setVisible(false);
        }
        _rb[i]->setStyleSheet("font: normal; font-size : 15px");
        _rb[i]->setChecked(false);
    }
    _grb->setExclusive(true);

    int numberOfAnswer = _tc->getActiveQuestion().getAnswered();
    if (numberOfAnswer != -1)
    {
        _rb[numberOfAnswer]->setStyleSheet("font: bold;  font-size : 15px");
        _rb[numberOfAnswer]->setChecked(true);
    }
}

void Widget::connectToDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase( "QMYSQL" );

      db.setHostName( "localhost" );
      db.setDatabaseName( "olia" );

      db.setUserName( "olia" );
      db.setPassword( "MyNewPass" );

      if( !db.open() )
      {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
      }

      qDebug( "Connected!" );
}

void Widget::handleNavigationButton(int bNumber)
{
    int n;

    switch (bNumber) {
    case 0:
        n = 0;
        break;
    case 1:
        n = _tc->getNumberOfActiveQuestion() - 1;
        break;
    case 2:
        n = _tc->getNumberOfActiveQuestion() + 1;
        break;
    case 3:
        n = _tc->getNumberOfQuestions() - 1;
        break;
    default:
        break;
    }

    if ((n >= 0) && (n < NumButtons * NumGridRows))
    {
        _tc->setActiveQuestion(n);
        repaintGroupBoxWithActiveQuestion(n);
        emit numberOfQuestionChanged(n);
    }
}

void Widget::handleTestButtons(int n)
{
    qDebug()<< n;
    if ((n >= 0) && (n < NumButtons * NumGridRows))
    {
        _tc->setActiveQuestion(n);
        repaintGroupBoxWithActiveQuestion(n);
        emit numberOfQuestionChanged(n);
    }
}

void Widget::handleRadioButtons(int n)
{
    for (int i = 0; i < MaxNumAnswers; ++i)
        if (i == n)
            _rb[i]->setStyleSheet("font: bold;  font-size : 15px");
        else
            _rb[i]->setStyleSheet("font: normal;  font-size : 15px");
    _testButtons[_tc->getNumberOfActiveQuestion()]->setIcon(QIcon("://icons/button_ok.png"));
    _tc->setAnswerOfActiveQuestion(n);
    qDebug()<< _tc->getActiveQuestion().getAnswered();
}

void Widget::handleCancelButton()
{
    int n =_tc->getNumberOfActiveQuestion();
    _tc->setAnswerOfActiveQuestion(-1);
    repaintGroupBoxWithActiveQuestion(n);
    _testButtons[n]->setIcon(QIcon());
}

void Widget::handleAcceptButton()
{
    QMessageBox* pmbx =
                        new QMessageBox("MessageBox",
                        QString::fromLocal8Bit(_tc->printTestResults().c_str()),
                        QMessageBox::Information,
                        QMessageBox::Yes,
                        QMessageBox::No,
                        QMessageBox::Cancel | QMessageBox::Escape);
    int n = pmbx->exec();
    delete pmbx;
    if (n == QMessageBox::Yes)
    {
        _tc->printTestResults();
    }

}

Widget::~Widget()
{
    delete ui;
}
