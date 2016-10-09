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

    QByteArray getPageId() const;

public slots:

    virtual void updatePage();

protected:

    QByteArray mToken;
    QByteArray mPageId;
};

#endif // QVKPAGEWIDGET_H
