#ifndef QVKPAGEWIDGET_H
#define QVKPAGEWIDGET_H

#include <QWidget>
#include <QByteArray>

class VkPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VkPageWidget(QWidget *parent = 0);

    void setToken(QByteArray token);

    bool isThisPage(const QString &pageName);

    QByteArray getPageId() const;
    QByteArray getPageName() const;

public slots:

    virtual void updatePage();

protected:

    QByteArray mToken;
    QByteArray mPageId;
    QByteArray mPageName;
};

#endif // QVKPAGEWIDGET_H
