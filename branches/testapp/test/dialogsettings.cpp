#include "dialogsettings.h"
#include "ui_dialogsettings.h"

#include <QMessageBox>
#include <QDate>
#include <QHostAddress>

#include "dialogautent.h"

#include "accountinfo.h"
#include "settings.h"

enum SettingsPage
{
    PAGE_ACCOUNTS
};

DialogSettings::DialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);

    if (windowIcon().isNull())
        setWindowIcon(QIcon(":/icons/icon-settings.svg"));

    if (ui->toolBox->itemIcon(PAGE_ACCOUNTS).isNull())
        ui->toolBox->setItemIcon(PAGE_ACCOUNTS, QIcon(":/icons/config-user.svg"));

    if (ui->buttonAccountAdd->icon().isNull())
        ui->buttonAccountAdd->setIcon(QIcon(":/icons/list-add.svg"));

    if (ui->buttonAccountRemove->icon().isNull())
        ui->buttonAccountRemove->setIcon(QIcon(":/icons/list-remove.svg"));

    updateAccountList();
}

DialogSettings::~DialogSettings()
{
    delete ui;
}

void DialogSettings::updateAccountList()
{
    ui->listAccounts->clear();

    AccountList accountList = getAccountList();

    foreach(AccountInfo accInfo, accountList)
    {
        QString name;
        QIcon icon;

        name = accInfo.visibleName();

        icon = accInfo.profileImage();

        QListWidgetItem *item = new QListWidgetItem(icon, name);

        item->setData(Qt::UserRole, QVariant::fromValue(accInfo));

        ui->listAccounts->addItem(item);
    }
}

void DialogSettings::on_buttonAccountRemove_clicked()
{
    QListWidgetItem *item = ui->listAccounts->currentItem();

    if (item)
    {
        AccountInfo accInfo = item->data(Qt::UserRole).value<AccountInfo>();

        QString text;

        text = QString("Удалить учетную запись '%1'?").arg(accInfo.visibleName());

        if (QMessageBox::question(this, "Подтверждение", text) == QMessageBox::No)
            return;

        //TODO: logout

        accInfo.dbDelete();

        updateAccountList();
    }
}

void DialogSettings::on_buttonAccountAdd_clicked()
{
    DialogAutent dialogAutent;

    if (dialogAutent.exec() != QDialog::Accepted)
        return;

    addUser(dialogAutent.getId(), dialogAutent.getLogin(),
            dialogAutent.getToken(), dialogAutent.getTokenExpire());

    updateAccountList();
}

void DialogSettings::on_listAccounts_currentRowChanged(int currentRow)
{
    ui->buttonAccountRemove->setEnabled(currentRow >= 0);
}
