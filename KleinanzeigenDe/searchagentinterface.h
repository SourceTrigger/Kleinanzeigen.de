#ifndef SEARCHAGENTINTERFACE_H
#define SEARCHAGENTINTERFACE_H

#include <QtCore>

enum PriceType {
  Negotiating = 1,
  FixPrice = 0,
  GiveAway = 2,
  Trade = 3,
  BestPrice = 4
};

class SearchResult
{
public:
    QString AdId; // max length 30
    QString AdTitle; // max length 255
    QString AdDescription;
    QString AdSeoUrl; // max length 255
    QDateTime AdStart;
    QDateTime AdEnd;
    QString AdImageUrl; // max length 255
    QString AdDistance; // max length 255, postalcode and city or distance
    int AdPrice = 0;
    PriceType AdPriceType = PriceType::Negotiating;
};

class SearchAgentInterface
{
public:
    virtual ~SearchAgentInterface() {}
    virtual QList<SearchResult> Search(const QUrl& rUrl, int rReadpages) = 0;
    virtual QString GetPlatformName() = 0;
    virtual QString GetPlatformHash() = 0;
    virtual QString GetLastError() = 0;
    virtual QString GetCustomerHelpMessage() = 0;
    virtual QString GetPlatformLetters() = 0;
    virtual bool SendQuestionToAdOwner(const QString &accountUsername, const QString &accountPassword, const QString &myName, const QString &myPhone, const QString &advertId) = 0;
};

#define SearchAgentInterface_iid "MG.AnzeigenChef.SearchAgentInterface"

Q_DECLARE_INTERFACE(SearchAgentInterface, SearchAgentInterface_iid)

#endif // SEARCHAGENTINTERFACE_H
