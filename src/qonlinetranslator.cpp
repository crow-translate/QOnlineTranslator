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

#include <QEventLoop>
#include <QMediaPlayer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "qonlinetranslator.h"

QString QOnlineTranslator::m_yandexSid;

bool QOnlineTranslator::m_secondSidRequest = false;

QOnlineTranslator::QOnlineTranslator(QObject *parent) :
    QObject(parent)
{}

QOnlineTranslator::QOnlineTranslator(const QString &text, Engine engine, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguageCode, QObject *parent) :
    QObject(parent)
{
    translate(text, engine, translationLanguage, sourceLanguage, translatorLanguageCode);
}

void QOnlineTranslator::translate(const QString &text, Engine engine, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguageCode)
{
    m_source = text;

    // Set languages
    m_sourceLanguageCode = sourceLanguage;
    if (translationLanguage == "auto")
        m_translationLanguageCode = systemLanguageCode();
    else
        m_translationLanguageCode = translationLanguage;
    if (translatorLanguageCode == "auto")
        m_translatorLanguageCode = systemLanguageCode();
    else
        m_translatorLanguageCode = translatorLanguageCode;

    // Reset old data
    m_translation.clear();
    m_translationTranslit.clear();
    m_sourceTranslit.clear();
    m_dictionaryList.clear();
    m_definitionsList.clear();
    m_error = false;

    QNetworkAccessManager network;
    QString unsendedText;
    switch (engine) {
    case Google:
        // Google has a limit of up to 5000 characters per translation request. If the query is larger, then it should be splited into several
        unsendedText = m_source;
        while (!unsendedText.isEmpty()) {
            int splitIndex = getSplitIndex(unsendedText, 5000); // Split the part by special symbol

            // Do not translate the part if it looks like garbage
            if (splitIndex == -1) {
                m_translation.append(unsendedText.left(5000));
                unsendedText = unsendedText.mid(5000);
                continue;
            }

            // Send request and check for errors
            QNetworkReply *apiReply = sendRequest("https://translate.googleapis.com/translate_a/single",
                                                 "client=gtx&ie=UTF-8&oe=UTF-8&dt=bd&dt=ex&dt=ld&dt=md&dt=rw&dt=rm&dt=ss&dt=t&dt=at&dt=qc&sl=" + m_sourceLanguageCode + "&tl=" + m_translationLanguageCode + "&hl=" + m_translatorLanguageCode + "&q=" + QUrl::toPercentEncoding(unsendedText.left(splitIndex)),
                                                 network);
            if (apiReply->error() != QNetworkReply::NoError) {
                m_error = true;
                m_translation = apiReply->errorString();
                return;
            }

            QByteArray replyData = apiReply->readAll();

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

            // Parse transliterations and source language
            m_translationTranslit.append(jsonData.at(0).toArray().last().toArray().at(2).toString());
            m_sourceTranslit.append(jsonData.at(0).toArray().last().toArray().at(3).toString());
            if (m_sourceLanguageCode == "auto")
                m_sourceLanguageCode = jsonData.at(2).toString();

            // Remove the parsed part from the next parsing
            unsendedText = unsendedText.mid(splitIndex);

            // Add a space between parts
            if (!unsendedText.isEmpty() && !m_translation.endsWith("\n")) {
                m_translation.append(" ");
                m_translationTranslit.append(" ");
                m_sourceTranslit.append(" ");
            }

            if (text.size() < 5000) {
                // Translation options
                foreach (QJsonValue translationOption, jsonData.at(1).toArray()) {
                    m_dictionaryList << QDictionary(translationOption.toArray().at(0).toString());
                    foreach (QJsonValue wordData, translationOption.toArray().at(2).toArray()) {
                        QString word = wordData.toArray().at(0).toString();
                        QString gender = wordData.toArray().at(4).toString();
                        QStringList translations;
                        foreach (auto translationForWord, wordData.toArray().at(1).toArray()) {
                           translations.append(translationForWord.toString());
                        }
                        m_dictionaryList.last().appendWord(word, gender, translations);
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
        break;
    case Yandex:
        // Get translation
        // Yandex has a limit of up to 150 characters per translation request. If the query is larger, then it should be splited into several.
        unsendedText = m_source;
        while (!unsendedText.isEmpty()) {
            int splitIndex = getSplitIndex(unsendedText, 150); // Split the part by special symbol

            // Do not translate the part if it looks like garbage
            if (splitIndex == -1) {
                m_translation.append(unsendedText.left(150));
                unsendedText = unsendedText.mid(150);
                continue;
            }

            // Need to get session ID from the web version in order to access the API
            if (m_yandexSid.isEmpty()) {
                QNetworkReply *webReply = generateYandexSid(network);
                if (webReply->error() != QNetworkReply::NoError) {
                    m_error = true;
                    m_translation = webReply->errorString();
                    return;
                }
            }

            // Send request and check for errors
            QNetworkReply *apiReply = sendRequest("https://translate.yandex.net/api/v1/tr.json/translate",
                                                 "id=" + m_yandexSid + "-0-0&srv=tr-text&text=" + QUrl::toPercentEncoding(unsendedText.left(splitIndex)) + "&lang=" + (sourceLanguage == "auto" ? m_translationLanguageCode : sourceLanguage + "-" + m_translationLanguageCode),
                                                 network);
            if (apiReply->error() != QNetworkReply::NoError) {
                if (apiReply->error() < 201) {
                    // Network errors
                    m_error = true;
                    m_translation = apiReply->errorString();
                    return;
                }
                if (apiReply->error() == QNetworkReply::ContentAccessDenied && !m_secondSidRequest) {
                    // Try to generate a new session ID second time, if the previous is invalid
                    m_yandexSid.clear();
                    m_secondSidRequest = true; // Do not generate the session ID third time if the second one was generated incorrectly
                    translate(m_source, Yandex, m_translationLanguageCode, m_sourceLanguageCode, m_translatorLanguageCode);
                    return;
                }
                else {
                    // Parse data to get request error type
                    QJsonDocument jsonResponse = QJsonDocument::fromJson(apiReply->readAll());
                    m_error = true;
                    m_secondSidRequest = false;
                    m_translation = jsonResponse.object().value("message").toString();
                    return;
                }
            }
            else
                m_secondSidRequest = false;

            // Parse translation data
            QJsonDocument jsonResponse = QJsonDocument::fromJson(apiReply->readAll());
            QJsonObject jsonData = jsonResponse.object();
            m_translation += jsonData.value("text").toArray().at(0).toString();
            if (m_sourceLanguageCode == "auto")
                m_sourceLanguageCode = jsonData.value("lang").toString().left(2);

            // Remove the parsed part from the next parsing
            unsendedText = unsendedText.mid(splitIndex);
        }

        // Get source transliteration
        // Do not request transliteration if the text is in English
        if (m_sourceLanguageCode != "en") {
            // Yandex has a limit of up to 180 characters per transliteration request. If the query is larger, then it should be splited into several.
            unsendedText = m_source;
            while (!unsendedText.isEmpty()) {
                int splitIndex = getSplitIndex(unsendedText, 180); // Split the part by special symbol

                // Do not translate the part if it looks like garbage
                if (splitIndex == -1) {
                    m_sourceTranslit.append(unsendedText.left(180));
                    unsendedText = unsendedText.mid(180);
                    continue;
                }

                // Send request and wait for the response
                QNetworkReply *apiReply = sendRequest("https://translate.yandex.net/translit/translit",
                                                     "text=" + QUrl::toPercentEncoding(unsendedText.left(splitIndex)) + "&lang=" + m_sourceLanguageCode,
                                                     network);
                if (apiReply->error() != QNetworkReply::NoError) {
                    m_error = true;
                    m_translation = apiReply->errorString();
                    return;
                }

                m_sourceTranslit += apiReply->readAll().mid(1).chopped(1);

                // Remove the parsed part from the next parsing
                unsendedText = unsendedText.mid(splitIndex);
            }
        }

        // Get translation transliteration
        // Do not request transliteration if the text is in English
        if (m_translatorLanguageCode != "en") {
            // Yandex has a limit of up to 180 characters per transliteration request. If the query is larger, then it should be splited into several.
            unsendedText = m_translation;
            while (!unsendedText.isEmpty()) {
                int splitIndex = getSplitIndex(unsendedText, 180); // Split the part by special symbol

                // Do not translate the part if it looks like garbage
                if (splitIndex == -1) {
                    m_translationTranslit.append(unsendedText.left(180));
                    unsendedText = unsendedText.mid(180);
                    continue;
                }

                // Send request and wait for the response
                QNetworkReply *apiReply = sendRequest("https://translate.yandex.net/translit/translit",
                                                     "text=" + QUrl::toPercentEncoding(unsendedText.left(splitIndex)) + "&lang=" + m_translationLanguageCode,
                                                     network);

                // Check for network error
                if (apiReply->error() != QNetworkReply::NoError) {
                    m_error = true;
                    m_translation = apiReply->errorString();
                    return;
                }

                m_translationTranslit += apiReply->readAll().mid(1).chopped(1);

                // Remove the parsed part from the next parsing
                unsendedText = unsendedText.mid(splitIndex);
            }
        }

        // Request dictionary data if only one word is translated.
        if (!m_translation.contains(" ")) {
            // Send request and wait for the response
            QNetworkReply *apiReply = sendRequest("http://dictionary.yandex.net/dicservice.json/lookupMultiple",
                                                 "text=" + m_source + "&dict=" + m_sourceLanguageCode + "-" + m_translationLanguageCode,
                                                 network);

            // Check for network error
            if (apiReply->error() != QNetworkReply::NoError) {
                m_error = true;
                m_translation = apiReply->errorString();
                return;
            }

            QJsonDocument jsonResponse = QJsonDocument::fromJson(apiReply->readAll());
            QJsonValue dictionary = jsonResponse.object().value(m_sourceLanguageCode + "-" + m_translationLanguageCode);
            foreach (QJsonValue dictionary, dictionary.toObject().value("regular").toArray()) {
                m_dictionaryList << QDictionary(dictionary.toObject().value("pos").toObject().value("text").toString());
                foreach (QJsonValue wordData, dictionary.toObject().value("tr").toArray()) {
                    QString word = wordData.toObject().value("text").toString();
                    QString gender = wordData.toObject().value("gen").toObject().value("text").toString();
                    QStringList translations;
                    foreach (QJsonValue translationForWord, wordData.toObject().value("mean").toArray()) {
                        translations.append(translationForWord.toObject().value("text").toString());
                    }
                    m_dictionaryList.last().appendWord(word, gender, translations);
                }
            }
        }
        break;
    }
}

QList<QMediaContent> QOnlineTranslator::sourceMedia(Engine engine, Speaker speaker, Emotion emotion) const
{
    return media(m_source, engine, m_sourceLanguageCode, speaker, emotion);
}

QList<QMediaContent> QOnlineTranslator::translationMedia(Engine engine, Speaker speaker, Emotion emotion) const
{
    return media(m_translation, engine, m_translation, speaker, emotion);
}

QString QOnlineTranslator::source() const
{
    return m_source;
}

QString QOnlineTranslator::sourceTranslit() const
{
    return m_sourceTranslit;
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

QString QOnlineTranslator::translationTranslit() const
{
    return m_translationTranslit;
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

QString QOnlineTranslator::translatorLanguageCode() const
{
    return m_translatorLanguageCode;
}

QList<QDictionary> QOnlineTranslator::dictionaryList() const
{
    return m_dictionaryList;
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
        translationLanguageCode = systemLanguageCode();

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

QString QOnlineTranslator::systemLanguageCode()
{
    QLocale locale;
    return locale.name().left(locale.name().indexOf("_"));
}

QList<QMediaContent> QOnlineTranslator::media(const QString &text, Engine engine, QString languageCode, Speaker speaker, Emotion emotion)
{
    QList<QMediaContent> mediaList;
    QString unparsedText = text;

    // Detect language if required
    if (languageCode == "auto") {
        QNetworkAccessManager network;
        switch (engine) {
        case Google: {
            // Wait for the response and send request
            QNetworkReply *reply = sendRequest("https://translate.googleapis.com/translate_a/single",
                                              "client=gtx&sl=auto&tl=en&dt=t&q=" + QUrl::toPercentEncoding(text.left(getSplitIndex(text, 5000))),
                                              network);

            if (reply->error() != QNetworkReply::NoError) {
                qDebug() << reply->errorString();
                return mediaList;
            }

            // Parse language
            languageCode = reply->readAll();
            languageCode.chop(4);
            languageCode = languageCode.mid(languageCode.lastIndexOf("\"") + 1);
            break;
        }
        case Yandex: {
            // Need to get session ID from the web version in order to access the API
            if (m_yandexSid.isEmpty()) {
                // Send request and wait for the response
                QNetworkReply *webReply = generateYandexSid(network);

                // Check for network error
                if (webReply->error() != QNetworkReply::NoError) {
                    qDebug() << webReply->errorString();
                    return mediaList;
                }
            }

            // Send request and wait for the response
            QNetworkReply *apiReply = sendRequest("https://translate.yandex.net/api/v1/tr.json/translate",
                                                 "id=" + m_yandexSid + "-0-0&srv=tr-text&text=" + QUrl::toPercentEncoding(text.left(getSplitIndex(text, 150))) + "&lang=en",
                                                 network);

            // Check for error
            if (apiReply->error() != QNetworkReply::NoError) {
                if (apiReply->error() < 201) {
                    qDebug() << apiReply->errorString();
                    return mediaList;
                }
                if (apiReply->error() == QNetworkReply::ContentAccessDenied && !m_secondSidRequest) {
                    // Try to generate a new session ID second time, if the previous is invalid
                    m_yandexSid.clear();
                    m_secondSidRequest = true; // Do not generate the session ID third time if the second one was generated incorrectly
                    return media(text, engine, languageCode, speaker, emotion);
                }
                else {
                    // Parse data to get request error type
                    QJsonDocument jsonResponse = QJsonDocument::fromJson(apiReply->readAll());
                    m_secondSidRequest = false;
                    return mediaList;
                }
            }
            else
                m_secondSidRequest = false;

            // Parse data
            QJsonDocument jsonResponse = QJsonDocument::fromJson(apiReply->readAll());
            QJsonObject jsonData = jsonResponse.object();
            languageCode = jsonData.value("lang").toString().right(2);
        }
        }
    }

    switch (engine) {
    case Google:
        // Google has a limit of up to 200 characters per tts request. If the query is larger, then it should be splited into several
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
        break;
    case Yandex:
        // Yandex tts support only 3 languages
        QString ttsLanguageCode;
        if (languageCode == "ru")
            ttsLanguageCode = "ru_RU";
        else if (languageCode == "en")
            ttsLanguageCode = "en_GB";
        else if (languageCode == "tr")
            ttsLanguageCode = "tr_TR";

        QString speakerCode = speakerString(speaker);
        QString emotionCode = emotionString(emotion);

        // Yandex has a limit of up to ~1400 characters per tts request. If the query is larger, then it should be splited into several
        while (!unparsedText.isEmpty()) {
            int splitIndex = getSplitIndex(unparsedText, 1400); // Split the part by special symbol

            // Generate URL API for add it to the playlist
            QUrl apiUrl("https://tts.voicetech.yandex.net/tts");
    #if defined(Q_OS_LINUX)
            apiUrl.setQuery("text=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)) +
                            "&lang=" + ttsLanguageCode +
                            "&speaker=" + speakerCode +
                            "&emotion=" + emotionCode +
                            "&format=mp3");
    #elif defined(Q_OS_WIN)
            apiUrl.setQuery("text=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)) +
                            "&lang=" + ttsLanguageCode +
                            "&speaker=" + speakerCode +
                            "&emotion=" + emotionCode +
                            "&format=mp3",R QUrl::DecodedMode);
    #endif
            mediaList.append(apiUrl);

            // Remove the said part from the next saying
            unparsedText = unparsedText.mid(splitIndex);
        }
        break;
    }

    return mediaList;
}

QNetworkReply *QOnlineTranslator::sendRequest(const QString &urlString, const QString &queryString, QNetworkAccessManager &network)
{
    // Generate API url
    QUrl url(urlString);
    url.setQuery(queryString);

    // Send request and wait for the response
    QNetworkReply *reply = network.get(QNetworkRequest(url));
    QEventLoop waitForResponse;
    connect(reply, &QNetworkReply::finished, &waitForResponse, &QEventLoop::quit);
    waitForResponse.exec();

    return reply;
}

QNetworkReply *QOnlineTranslator::generateYandexSid(QNetworkAccessManager &network)
{
    // Send request and wait for the response
    QNetworkReply *webReply = sendRequest("https://translate.yandex.com/", "", network);

    if (webReply->error() == QNetworkReply::NoError) {
        // Parse session ID from downloaded page
        QByteArray replyData = webReply->readAll();
        QString sid = replyData.mid(replyData.indexOf("SID: '") + 6, 26);

        // Yandex show reversed parts of session ID, need to decode
        QStringList sidParts = sid.split(".");
        for (short i = 0; i < sidParts.size(); ++i)
            std::reverse(sidParts[i].begin(), sidParts[i].end());

        m_yandexSid = sidParts.join(".");
    }
    return webReply;
}

QString QOnlineTranslator::speakerString(QOnlineTranslator::Speaker speaker)
{
    QString speakerString;
    switch (speaker) {
    case Zahar:
        speakerString = "zahar";
        break;
    case Ermil:
        speakerString = "ermil";
        break;
    case Jane:
        speakerString = "jane";
        break;
    case Oksana:
        speakerString = "oksana";
        break;
    case Alyss:
        speakerString = "alyss";
        break;
    case Omazh:
        speakerString = "omazh";
        break;
    }

    return speakerString;
}

QString QOnlineTranslator::emotionString(QOnlineTranslator::Emotion emotion)
{
    QString emotionString;
    switch (emotion) {
    case Good:
        emotionString = "good";
        break;
    case Evil:
        emotionString = "evil";
        break;
    case Neutral:
        emotionString = "neutral";
        break;
    }

    return emotionString;
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
