#ifndef QVKPAGEWIDGET_H
#define QVKPAGEWIDGET_H

#include <QWidget>
#include <QByteArray>
#include <QUrl>
#include <QLabel>
#include <QTimer>
#include <QList>
#include <QBoxLayout>

class VkPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VkPageWidget(QWidget *parent = 0);

    void setToken(QByteArray token);

    bool isThisPage(const QString &pageName);

    QByteArray getPageId() const;
    QByteArray getPageName() const;

    virtual QUrl getPageUrl() const = 0;

    void setPageContent(QWidget *pageContent, QBoxLayout *mainlayout);

private:

    QWidget *mPageContent;
    QWidget *mPageLoading;
    QWidget *mPageError;

    QLabel  *mPageErrorText;

    QLabel *mLoadingAnimation;
    QTimer mLoadingAnimationTimer;

    QList<QPixmap> mLoadingAnimationImageList;
    unsigned int mLoadingAnimationCount;

    unsigned int mLoadingAnimationIndex;

protected:

    enum PageStatus
    {
        PAGE_LOADING,
        PAGE_LOADED,
        PAGE_ERROR
    };

    PageStatus mPageStatus;

    QByteArray mToken;
    QByteArray mPageId;
    QByteArray mPageName;

    void setPageStatus(const PageStatus &pageStatus);

public slots:

    virtual void updatePage();

    void setError(const QString &errorText);

private slots:

    void updateAnimation();

};

#endif // QVKPAGEWIDGET_H
