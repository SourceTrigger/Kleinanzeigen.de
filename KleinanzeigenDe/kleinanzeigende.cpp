#include "kleinanzeigende.h"
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkAccessManager>

KleinanzeigenDe::KleinanzeigenDe(QObject *parent)
{
    qInfo() << GetPlatformName() << "loaded";
    Q_UNUSED(parent);
}

QList<SearchResult> KleinanzeigenDe::Search(const QUrl &url, int readpages)
{
    bool doNext = true;
    int currentpage = 1;
    QUrl nextUrl = url;

    while(doNext)
    {
        doNext = false;

        QUrlQuery noneQuery;
        QString htmlSource = GetHtmlSourceCode(nextUrl.toString(), noneQuery);



        currentpage++;
        if (currentpage>readpages)
            break;
    }

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



/**
 * @brief KleinanzeigenDe::GetHtmlSourceCode
 * @param rUrl Source URL
 * @param rPost Any Postfields if needed, else use GET
 * @return HTML Source Code
 */
QString KleinanzeigenDe::GetHtmlSourceCode(const QString &url, const QUrlQuery &post)
{
    QNetworkAccessManager manager;

    QUrl uri(url);
    QEventLoop eventLoop;

    QNetworkRequest request(uri);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);

    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply;
    if (post.isEmpty())
        reply = manager.get(request);
    else
        reply = manager.post(request,post.toString(QUrl::FullyEncoded).toUtf8());
    eventLoop.exec();

    QString responseString = "";
    auto error_type = reply->error();
    if (error_type == QNetworkReply::NoError) {
        responseString = reply->readAll();
    } else {
        lastError = reply->errorString();
    }

    reply->deleteLater();
    manager.deleteLater();

    return responseString;
}

/**
 * @brief KleinanzeigenDe::GetPartOfString
 * @param rSourceString String to parse
 * @param rFromString Begin of part
 * @param rToString End of part
 * @return SubString of begin and end, return empty String if not found
 */
QString KleinanzeigenDe::GetPartOfString(const QString &sourceString, const QString &fromString, const QString &toString)
{
    QString src = sourceString;

    if (src.isEmpty())
        return "";

    int start = 0;
    if (fromString != "")
    {
        start = src.indexOf(fromString);
        if (start >= 0)
        {
            start += fromString.length();
            int end = src.length();
            if (toString != "")
            {
                end = src.indexOf(toString, start);
                if (end < 0) return "";
            }
            return src.mid(start, end - start);
        }
        else
        {
            return "";
        }
    }
    else
    {
        int end = src.length();
        if (toString != "")
        {
            end = src.indexOf(toString, start + fromString.length());
            if (end < 0) return "";
        }
        if (end - start < 0)
        {
            return "";
        }
        return src.mid(start, end - start);
    }
}
