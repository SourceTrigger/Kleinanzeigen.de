#ifndef KLEINANZEIGENDE_H
#define KLEINANZEIGENDE_H

#include "searchagentinterface.h"
#include <QGenericPlugin>
#include <QColor>
#include <QNetworkAccessManager>

class KleinanzeigenDe : public QObject, public SearchAgentInterface
{
    Q_OBJECT
        Q_INTERFACES(SearchAgentInterface)
    Q_PLUGIN_METADATA(IID "MG.AnzeigenChef.SearchAgentInterface" FILE "KleinanzeigenDe.json")
private:
    QString userAgent = "Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.20 (KHTML, like Gecko) Chrome/11.0.672.2 Safari/534.20";
    QString lastError;
    QString GetHtmlSourceCode(const QString &url, const QUrlQuery &post);
    QString GetPartOfString(const QString &sourceString, const QString &fromString, const QString &toString);

public:
    KleinanzeigenDe(QObject *parent = 0);
    QList<SearchResult> Search(const QUrl& url, int readpages) override;
    QString GetPlatformName() override;
    QColor GetPlatformColor() override;
    QString GetPlatformHash() override;
    QString GetLastError() override;
    QString GetCustomerHelpMessage() override;
    QString GetPlatformLetters() override;
    bool SendQuestionToAdOwner(const QString &accountUsername, const QString &accountPassword, const QString &myName, const QString &myPhone, const QString &advertId) override;
};

#endif // KLEINANZEIGENDE_H
