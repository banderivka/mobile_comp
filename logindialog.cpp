#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    setUpGUI();
    setWindowTitle( tr("User Login") );
    setModal( true );
}

void LoginDialog::setUpGUI(){

    w = new Widget();

    QGridLayout* formGridLayout = new QGridLayout( this );

    editUsername = new QLineEdit( this );

    editPassword = new QLineEdit( this );
    editPassword->setEchoMode( QLineEdit::Password );

    labelUsername = new QLabel( this );
    labelPassword = new QLabel( this );
    labelInfo = new QLabel( this );

    labelUsername->setText( tr( "Username" ) );
    labelUsername->setBuddy( editUsername );
    labelPassword->setText( tr( "Password" ) );
    labelPassword->setBuddy( editPassword );



    buttons = new QDialogButtonBox( this );
    buttons->addButton( QDialogButtonBox::Ok );
    buttons->addButton( QDialogButtonBox::Cancel );
    buttons->button( QDialogButtonBox::Ok )->setText( tr("Логін") );
    buttons->button( QDialogButtonBox::Cancel )->setText( tr("Скасувати") );

    connect( buttons->button( QDialogButtonBox::Cancel ),
             SIGNAL(pressed()),
             this,
             SLOT(close())
             );

    connect( buttons->button( QDialogButtonBox::Ok ),
             SIGNAL(pressed()),
             this,
             SLOT(slotAcceptLogin()) );

    formGridLayout->addWidget( labelUsername, 0, 0 );
    formGridLayout->addWidget( editUsername, 0, 1 );
    formGridLayout->addWidget( labelPassword, 1, 0 );
    formGridLayout->addWidget( editPassword, 1, 1 );
    formGridLayout->addWidget( labelInfo, 2, 0, 1, 2 );
    formGridLayout->addWidget( buttons, 3, 0, 1, 2 );

    setLayout( formGridLayout );
}


void LoginDialog::setUsername(std::string &username){

    editUsername->setText( QString::fromLocal8Bit(username.c_str()) );

    editPassword->setFocus();
}


void LoginDialog::setPassword(std::string &password){
    editPassword->setText( QString::fromLocal8Bit(password.c_str()) );
}

void LoginDialog::slotAcceptLogin(){
    std::string username = editUsername->text().toStdString();
    std::string password = editPassword->text().toStdString();

    labelInfo->setText("");
    if (username.size() == 0 || (password.size() == 0))
    {
        labelInfo->setText("Не всі поля заповнені!");
        return;
    }

    std::ifstream file;
    file.open ( "../mobile_comp/files/authdata.txt", std::ifstream::in );
    qDebug() << file.is_open();
    std::string fusername, fpassword;


    while (file) {
        std::getline(file, fusername, '\t');
        std::getline(file, fpassword);

        qDebug() << QString::fromLocal8Bit(fusername.c_str());
        qDebug() << QString::fromLocal8Bit(fpassword.c_str());


        if (fusername == username && fpassword == password)
        {
            w->show();
            this->setVisible(false);
        }
    }

    labelInfo->setText("Невірний логін/пароль!");
    buttons->button( QDialogButtonBox::Ok )->setChecked(false);
    return;
}
