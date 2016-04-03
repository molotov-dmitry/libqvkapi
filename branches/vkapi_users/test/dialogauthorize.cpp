#include "dialogauthorize.h"
#include "ui_dialogauthorize.h"

#include "accountinfo.h"
#include "dialogsettings.h"

#include <QListView>

DialogAuthorize::DialogAuthorize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAuthorize)
{
    ui->setupUi(this);

    if (windowIcon().isNull())
        setWindowIcon(QIcon(":/icons/icon-auth.svg"));

    if (ui->buttonSettings->icon().isNull())
        ui->buttonSettings->setIcon(QIcon(":/icons/configure.svg"));

    updateAccountList();

}

DialogAuthorize::~DialogAuthorize()
{
    delete ui;
}

void DialogAuthorize::on_buttonSettings_clicked()
{
    DialogSettings dialogSettings;
    dialogSettings.exec();

    updateAccountList();
}

void DialogAuthorize::on_buttonExit_clicked()
{

}

void DialogAuthorize::on_buttonLogin_clicked()
{
    if (ui->listAccounts->currentIndex() >= 0)
    {
        mCurrentAccountInfo = ui->listAccounts->currentData(Qt::UserRole).value<AccountInfo>();

        accept();
    }
}

AccountInfo DialogAuthorize::currentAccountInfo() const
{
    return mCurrentAccountInfo;
}

void DialogAuthorize::updateAccountList()
{
    ui->listAccounts->clear();

    AccountList accountList = getAccountList();

    foreach(AccountInfo accInfo, accountList)
    {
        QString  name;
        QIcon    icon;
        QVariant accData;

        name = accInfo.visibleName();

        icon = accInfo.profileImage();

        accData = QVariant::fromValue(accInfo);

        ui->listAccounts->addItem(icon, name, accData);
    }

    ui->buttonLogin->setEnabled(ui->listAccounts->count() > 0);
}
