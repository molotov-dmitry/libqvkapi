#include "dialogautent.h"
#include "ui_dialogautent.h"

DialogAutent::DialogAutent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAutent)
{
    ui->setupUi(this);
}

DialogAutent::~DialogAutent()
{
    delete ui;
}

void DialogAutent::setLogin(const QString &login)
{
    ui->editLogin->setText(login);
}

QString DialogAutent::getLogin() const
{
    return ui->editLogin->text();
}

QString DialogAutent::getPassword() const
{
    return ui->editPassword->text();
}

void DialogAutent::on_buttonPasswordVisible_toggled(bool checked)
{
    if (checked)
        ui->editPassword->setEchoMode(QLineEdit::Normal);
    else
        ui->editPassword->setEchoMode(QLineEdit::Password);
}
