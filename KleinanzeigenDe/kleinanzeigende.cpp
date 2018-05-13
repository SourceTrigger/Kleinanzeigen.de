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
    QList<SearchResult> results;

    while(doNext)
    {
        doNext = false;

        QUrlQuery noneQuery;
        QString htmlSource = GetHtmlSourceCode(nextUrl.toString(), noneQuery);

        while(htmlSource.contains("srl-item-cont"))
        {
            int p1 = htmlSource.indexOf("srl-item-cont");
            int p2 = htmlSource.indexOf("itemprop=\"price\"", p1);
            if (p2 > 0)
                p2 = htmlSource.indexOf(">",p2)+1;

            QString part = htmlSource.mid(p1, p2-p1);

            SearchResult sr;

            sr.AdTitle = GetPartOfString(part,"itemprop=\"name\"",">");
            sr.AdTitle = GetPartOfString(sr.AdTitle, "content=\"","\"");

            sr.AdDescription = GetPartOfString(part,"itemprop=\"description\"",">")+">";
            sr.AdDescription = GetPartOfString(sr.AdDescription, "content=\"","\">");

            sr.AdSeoUrl = GetPartOfString(part,"itemprop=\"url\"",">");
            sr.AdSeoUrl = GetPartOfString(sr.AdSeoUrl, "content=\"","\"");

            // ?? :)
            sr.AdDistance = GetPartOfString(part,">D-","<");

            QStringList ir = sr.AdSeoUrl.split("-");
            if (ir.count()>0)
                sr.AdId = ir.last();
            sr.AdId = GetPartOfString(sr.AdId, "", ".");
            qInfo() << sr.AdId << sr.AdTitle;

            sr.AdImageUrl = GetPartOfString(part,"itemprop=\"image\"",">");
            sr.AdImageUrl = GetPartOfString(sr.AdImageUrl, "content=\"","\"");
            if (!sr.AdImageUrl.toLower().contains("https"))
                sr.AdImageUrl = "https:" + sr.AdImageUrl;

            QString price = GetPartOfString(part,"itemprop=\"price\"",">");
            price = GetPartOfString(price, "content=\"","\"");
            if (price.contains(","))
                price = price.left(price.indexOf(","));
            sr.AdPrice = price.toInt();

            sr.AdStart = QDateTime::currentDateTime().addDays(-1);
            sr.AdEnd = QDateTime::currentDateTime().addDays(30);

            results.append(sr);

            htmlSource.remove(0,p2);
        }

        currentpage++;
        if (currentpage>readpages)
            break;
    }

    return results;
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
    request.setRawHeader( "Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.7" );

    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply;
    if (post.isEmpty())
        reply = manager.get(request);
    else
        reply = manager.post(request,post.toString(QUrl::FullyEncoded).toUtf8());
    eventLoop.exec();

    QString responseString;
    auto error_type = reply->error();
    if (error_type == QNetworkReply::NoError)
    {
        QByteArray p = reply->readAll();
        responseString = QString::fromLatin1(p, p.size());
    }
    else
    {
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
