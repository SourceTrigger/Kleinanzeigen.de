#include "kleinanzeigende.h"
#include <QDebug>

KleinanzeigenDe::KleinanzeigenDe(QObject *parent)
{
    qInfo() << GetPlatformName() << "loaded";
    Q_UNUSED(parent);
}

QList<SearchResult> KleinanzeigenDe::Search(const QUrl &url, int readpages)
{
    qInfo() << "IS TRIGGERED";
    SearchResult result;
    result.AdDescription = "Hallo Welt";
    result.AdId = "12345677";
    result.AdTitle = "Hallo Welt";
    result.AdPrice = 10;
    result.AdEnd = QDateTime::currentDateTime().addDays(30);
    result.AdStart = QDateTime::currentDateTime().addDays(-30);
    result.AdDistance = "50km";
    QList<SearchResult> test;
    test.append(result);
    return test;
}

QString KleinanzeigenDe::GetPlatformName()
{
    return "Kleianzeigen.de";
}

QString KleinanzeigenDe::GetPlatformHash()
{
    return "Kleinanzeigen.de#1#1";
}

QString KleinanzeigenDe::GetLastError()
{
    return lastError;
}

QString KleinanzeigenDe::GetCustomerHelpMessage()
{
    return "";
}

QString KleinanzeigenDe::GetPlatformLetters()
{
    return "K";
}

bool KleinanzeigenDe::SendQuestionToAdOwner(const QString &accountUsername, const QString &accountPassword, const QString &myName, const QString &myPhone, const QString &advertId)
{
    return false; // not implemented
}
