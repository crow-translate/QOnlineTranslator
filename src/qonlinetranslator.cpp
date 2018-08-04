/*
 *  Copyright © 2018 Gennady Chernyshchuk <genaloner@gmail.com>
 *
 *  This file is part of QOnlineTranslator.
 *
 *  QOnlineTranslator is free library; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a get of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QMediaPlayer>
#include <QJsonDocument>
#include <QJsonArray>

#include "qonlinetranslator.h"

QOnlineTranslator::QOnlineTranslator(QObject *parent) :
    QObject(parent)
{}

QOnlineTranslator::QOnlineTranslator(const QString &text, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguageCode, const bool &autoCorrect, QObject *parent) :
    QObject(parent)
{
    translate(text, translationLanguage, sourceLanguage, translatorLanguageCode, autoCorrect);
}

void QOnlineTranslator::translate(const QString &text, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguageCode, const bool &autoCorrect)
{
    m_source = text;

    // Detect system language if translateLanguage not specified
    if (translationLanguage == "auto")
        m_translationLanguageCode = defaultLocaleToCode();
    else
        m_translationLanguageCode = translationLanguage;

    // Set auto-correction query option
    QString autocorrection;
    if (autoCorrect == true)
        autocorrection = "qca";
    else
        autocorrection = "qc";

    // Reset old data
    m_translation.clear();
    m_translationTranscription.clear();
    m_sourceTranscription.clear();
    m_sourceLanguageCode.clear();
    m_translationOptionsList.clear();
    m_definitionsList.clear();
    m_error = false;

    // Google has a limit of up to 5000 characters per translation request. If the query is larger, then it should be splited into several
    QString untranslatedText = text;
    while (!untranslatedText.isEmpty()) {
        int splitIndex = getSplitIndex(untranslatedText, 5000); // Split the part by special symbol
        if (splitIndex == -1) {
            // Do not translate the part if it looks like garbage
            m_translation.append(untranslatedText.left(5000));
            untranslatedText = untranslatedText.mid(5000);
            continue;
        }

        // Generate API url
        QUrl apiUrl("https://translate.googleapis.com/translate_a/single");
        apiUrl.setQuery("client=gtx&ie=UTF-8&oe=UTF-8&dt=bd&dt=ex&dt=ld&dt=md&dt=rw&dt=rm&dt=ss&dt=t&dt=at&dt=" + autocorrection +"&sl=" + sourceLanguage + "&tl=" +
                        translationLanguage + "&hl=" + translatorLanguageCode + "&q=" + QUrl::toPercentEncoding(untranslatedText.left(splitIndex)));
        
        // Send request
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(apiUrl));

        // Wait for the response
        QEventLoop event;
        connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
        event.exec();

        // Check for network error
        if (reply->error() != QNetworkReply::NoError) {
            m_error = true;
            m_translation = reply->errorString();
            return;
        }

        QByteArray replyData = reply->readAll();

        // Check availability of service
        if (replyData.startsWith("<")) {
            m_error = true;
            m_translation = tr("Google systems have detected unusual traffic from your computer network. Please try your request again later.");
            return;
        }

        // Convert to JsonArray
        QJsonDocument jsonResponse = QJsonDocument::fromJson(replyData);
        QJsonArray jsonData = jsonResponse.array();

        // Parse first sentense. If the answer contains more than one sentence, then at the end of the first one there will be a space
        m_translation.append(jsonData.at(0).toArray().at(0).toArray().at(0).toString());
        for (int i = 1; m_translation.endsWith(" ") || m_translation.endsWith("\n") || m_translation.endsWith("\u00a0"); i++)
            m_translation.append(jsonData.at(0).toArray().at(i).toArray().at(0).toString());

        // Parse transcriptions and source language
        m_translationTranscription.append(jsonData.at(0).toArray().last().toArray().at(2).toString());
        m_sourceTranscription.append(jsonData.at(0).toArray().last().toArray().at(3).toString());
        if (m_sourceLanguageCode.isEmpty())
            m_sourceLanguageCode = jsonData.at(2).toString();

        // Remove the parsed part from the next parsing
        untranslatedText = untranslatedText.mid(splitIndex);

        // Add a space between parts
        if (!untranslatedText.isEmpty() && !m_translation.endsWith("\n")) {
            m_translation.append(" ");
            m_translationTranscription.append(" ");
            m_sourceTranscription.append(" ");
        }

        if (text.size() < 5000) {
            // Translation options
            foreach (QJsonValue translationOption, jsonData.at(1).toArray()) {
                m_translationOptionsList << QTranslationOptions(translationOption.toArray().at(0).toString());
                foreach (QJsonValue word, translationOption.toArray().at(2).toArray()) {
                    m_translationOptionsList.last().appendOption(word.toArray().at(0).toString(), word.toArray().at(4).toString());
                    foreach (auto translationsForWord, word.toArray().at(1).toArray()) {
                        m_translationOptionsList.last().appendTranslation(translationsForWord.toString());
                    }
                }
            }

            // Definitions
            foreach (QJsonValue definition, jsonData.at(12).toArray()) {
                m_definitionsList << QDefinition();
                m_definitionsList.last().setTypeOfSpeech(definition.toArray().at(0).toString());
                m_definitionsList.last().setDescription(definition.toArray().at(1).toArray().at(0).toArray().at(0).toString());
                m_definitionsList.last().setExample(definition.toArray().at(1).toArray().at(0).toArray().at(2).toString());
            }
        }
    }
}

QList<QMediaContent> QOnlineTranslator::sourceMedia() const
{
    QList<QMediaContent> mediaList;

    // Google has a limit of up to 200 characters per tts request. If the query is larger, then it should be splited into several
    QString unparsedText = m_source;
    while (!unparsedText.isEmpty()) {
        int splitIndex = getSplitIndex(unparsedText, 200); // Split the part by special symbol

        // Generate URL API for add it to the playlist
        QUrl apiUrl("http://translate.googleapis.com/translate_tts");
#if defined(Q_OS_LINUX)
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + m_sourceLanguageCode +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)));
#elif defined(Q_OS_WIN)
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + m_sourceLanguageCode +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)), QUrl::DecodedMode);
#endif
        mediaList.append(apiUrl);

        // Remove the said part from the next saying
        unparsedText = unparsedText.mid(splitIndex);
    }
    return mediaList;
}

QList<QMediaContent> QOnlineTranslator::translationMedia() const
{
    QList<QMediaContent> mediaList;

    // Google has a limit of up to 200 characters per tts request. If the query is larger, then it should be splited into several
    QString unparsedText = m_translation;
    while (!unparsedText.isEmpty()) {
        int splitIndex = getSplitIndex(unparsedText, 200); // Split the part by special symbol

        // Generate URL API for add it to the playlist
        QUrl apiUrl("http://translate.googleapis.com/translate_tts");
#if defined(Q_OS_LINUX)
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + m_translationLanguageCode +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)));
#elif defined(Q_OS_WIN)
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + m_translationLanguageCode +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)), QUrl::DecodedMode);
#endif
        mediaList.append(apiUrl);

        // Remove the said part from the next saying
        unparsedText = unparsedText.mid(splitIndex);
    }
    return mediaList;
}

QString QOnlineTranslator::source() const
{
    return m_source;
}

QString QOnlineTranslator::sourceTranscription() const
{
    return m_sourceTranscription;
}

QString QOnlineTranslator::sourceLanguageCode() const
{
    return m_sourceLanguageCode;
}

QString QOnlineTranslator::sourceLanguage() const
{
    int index = m_languageCodes.indexOf(m_sourceLanguageCode);
    if (index == -1) {
        qDebug() << tr("Unable to find language with code ") << m_sourceLanguageCode;
        return tr("Unknown");
    }
    else
        return m_languageNames.at(index);
}

QString QOnlineTranslator::translation() const
{
    return m_translation;
}

QString QOnlineTranslator::translationTranscription() const
{
    return m_translationTranscription;
}

QString QOnlineTranslator::translationLanguageCode() const
{
    return m_translationLanguageCode;
}

QString QOnlineTranslator::translationLanguage() const
{
    int index = m_languageCodes.indexOf(m_translationLanguageCode);
    if (index == -1) {
        qDebug() << tr("Unable to find language for code ") << m_translationLanguageCode;
        return tr("Unknown");
    }
    else
        return m_languageNames.at(index);
}

QList<QTranslationOptions> QOnlineTranslator::translationOptionsList() const
{
    return m_translationOptionsList;
}

QList<QDefinition> QOnlineTranslator::definitionsList() const
{
    return m_definitionsList;
}

bool QOnlineTranslator::error() const
{
    return m_error;
}

QStringList QOnlineTranslator::languages() const
{
    return m_languageNames;
}

QStringList QOnlineTranslator::codes() const
{
    return m_languageCodes;
}

QString QOnlineTranslator::codeToLanguage(const QString &code) const
{
    int index = m_languageCodes.indexOf(code);
    if (index == -1) {
        qDebug() << tr("Unable to find language for code ") << code;
        return tr("Unknown");
    }
    else
        return m_languageNames.at(index);
}

QString QOnlineTranslator::languageToCode(const QString &language) const
{
    int index = m_languageNames.indexOf(language);
    if (index == -1) {
        qDebug() << tr("Unable to find code for language ") << language;
        return "null";
    }
    else
        return m_languageCodes.at(index);
}

QString QOnlineTranslator::translateText(const QString &text, QString translationLanguageCode, QString sourceLanguageCode)
{
    // Detect system language if translationLanguage not specified
    if (translationLanguageCode == "auto")
        translationLanguageCode = defaultLocaleToCode();

    QString untranslatedText = text;
    QString translatedText;

    // Google has a limit of up to 5000 characters per translation request. If the query is larger, then it should be splited into several
    while (!untranslatedText.isEmpty()) {
        int splitIndex = getSplitIndex(untranslatedText, 5000); // Split part by special symbols
        if (splitIndex == -1) {
            // Do not translate the part if it looks like garbage
            translatedText.append(untranslatedText.left(5000));
            untranslatedText = untranslatedText.mid(5000);
            continue;
        }

        // Generate short URL API only for translation and and receive a reply
        QUrl apiUrl("https://translate.googleapis.com/translate_a/single");
        apiUrl.setQuery("client=gtx&sl=" + sourceLanguageCode +"&tl=" + translationLanguageCode + "&dt=t&q=" + QUrl::toPercentEncoding(untranslatedText.left(splitIndex)));

        // Send request
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(apiUrl));

        // Wait for the response
        QEventLoop event;
        connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
        event.exec();

        // Check for network error
        if (reply->error() != QNetworkReply::NoError)
            return reply->errorString();

        // Convert to JsonArray
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonArray jsonData = jsonResponse.array();

        // Parse first sentense. If the answer contains more than one sentence, then at the end of the first one there will be a space
        translatedText.append(jsonData.at(0).toArray().at(0).toArray().at(0).toString());
        for (int i = 1; translatedText.endsWith(" ") || translatedText.endsWith("\n") || translatedText.endsWith("\u00a0"); i++)
            translatedText.append(jsonData.at(0).toArray().at(i).toArray().at(0).toString());

        // Remove the parsed part from the next parsing
        untranslatedText = untranslatedText.mid(splitIndex);

        // Add a space between parts
        if (!untranslatedText.isEmpty() && !translatedText.endsWith("\n"))
            translatedText.append(" ");
    }

    return translatedText;
}

QString QOnlineTranslator::defaultLocaleToCode()
{
    QLocale locale;
    return locale.name().left(locale.name().indexOf("_"));
}

QList<QMediaContent> QOnlineTranslator::media(const QString &text, QString languageCode)
{
    QList<QMediaContent> mediaList;

    // Google don't support "auto" as argument for text-to-speech, so need to detect language manually from translation request
    if (languageCode == "auto") {
        QUrl languageUrl("https://translate.googleapis.com/translate_a/single");
        languageUrl.setQuery("client=gtx&sl=auto&tl=en&dt=t&q=" + QUrl::toPercentEncoding(text.left(getSplitIndex(text, 5000))));

        // Send request
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(languageUrl));

        // Wait for the response
        QEventLoop event;
        connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
        event.exec();

        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            return mediaList;
        }

        // Parse language
        languageCode = reply->readAll();
        languageCode.chop(4);
        languageCode = languageCode.mid(languageCode.lastIndexOf("\"") + 1);
    }

    // Google has a limit of up to 200 characters per tts request. If the query is larger, then it should be splited into several
    QString unparsedText = text;
    while (!unparsedText.isEmpty()) {
        int splitIndex = getSplitIndex(unparsedText, 200); // Split the part by special symbol

        // Generate URL API for add it to the playlist
        QUrl apiUrl("http://translate.googleapis.com/translate_tts");
#if defined(Q_OS_LINUX)
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + languageCode +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)));
#elif defined(Q_OS_WIN)
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + languageCode +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)), QUrl::DecodedMode);
#endif
        mediaList.append(apiUrl);

        // Remove the said part from the next saying
        unparsedText = unparsedText.mid(splitIndex);
    }
    return mediaList;
}

// Get split index of the text according to the limit
int QOnlineTranslator::getSplitIndex(const QString &untranslatedText, int limit)
{
    if (untranslatedText.size() < limit)
        return limit;

    int splitIndex = untranslatedText.lastIndexOf(". ", limit - 1);
    if (splitIndex != -1)
        return splitIndex + 1;

    splitIndex = untranslatedText.lastIndexOf(" ", limit - 1);
    if (splitIndex != -1)
        return splitIndex + 1;

    splitIndex = untranslatedText.lastIndexOf("\n", limit - 1);
    if (splitIndex != -1)
        return splitIndex + 1;

    // Non-breaking gap
    splitIndex = untranslatedText.lastIndexOf("\u00a0", limit - 1);
    if (splitIndex != -1)
        return splitIndex + 1;

    // If the text has not passed any check and is most likely garbage
    return limit;
}
