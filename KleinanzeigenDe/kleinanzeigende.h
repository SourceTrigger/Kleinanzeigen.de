#ifndef KLEINANZEIGENDE_H
#define KLEINANZEIGENDE_H

#include "searchagentinterface.h"
#include <QGenericPlugin>
#include <QNetworkAccessManager>

class KleinanzeigenDe : public QObject, public SearchAgentInterface
{
    Q_OBJECT
        Q_INTERFACES(SearchAgentInterface)
    Q_PLUGIN_METADATA(IID "MG.AnzeigenChef.SearchAgentInterface" FILE "KleinanzeigenDe.json")
private:
    QString lastError;

public:
    KleinanzeigenDe(QObject *parent = 0);
    QList<SearchResult> Search(const QUrl& url, int readpages) override;
    QString GetPlatformName() override;
    QString GetPlatformHash() override;
    QString GetLastError() override;
    QString GetCustomerHelpMessage() override;
    QString GetPlatformLetters() override;
    bool SendQuestionToAdOwner(const QString &accountUsername, const QString &accountPassword, const QString &myName, const QString &myPhone, const QString &advertId) override;
};

#endif // KLEINANZEIGENDE_H
