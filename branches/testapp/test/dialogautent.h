#ifndef DIALOGAUTENT_H
#define DIALOGAUTENT_H

#include <QDialog>

namespace Ui {
class DialogAutent;
}

class DialogAutent : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAutent(QWidget *parent = 0);
    ~DialogAutent();

    void setLogin(const QString &login);

    QString getLogin() const;
    QString getPassword() const;

private slots:
    void on_buttonPasswordVisible_toggled(bool checked);

private:
    Ui::DialogAutent *ui;
};

#endif // DIALOGAUTENT_H
