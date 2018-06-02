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

#if defined(Q_OS_WIN)
#include <QBuffer>
#endif

#include "qonlinetranslator.h"

const QStringList QOnlineTranslator::LANGUAGE_NAMES = { tr("Automatically detect"), tr("Afrikaans"), tr("Amharic"), tr("Arabic"), tr("Azerbaijani"), tr("Belarusian"),
                                                        tr("Bulgarian"), tr("Bengali"), tr("Bosnian"), tr("Catalan"), tr("Cebuano"), tr("Corsican"), tr("Czech"),
                                                        tr("Welsh"), tr("Danish"), tr("German"), tr("Greek"), tr("English"), tr("Esperanto"), tr("Spanish"),
                                                        tr("Estonian"), tr("Basque"), tr("Persian"), tr("Finnish"), tr("Fijian"), tr("French"), tr("Frisian"), tr("Irish"),
                                                        tr("Scots Gaelic"), tr("Galician"), tr("Gujarati"), tr("Hausa"), tr("Hawaiian"), tr("Hebrew"), tr("Hindi"),
                                                        tr("Hmong"), tr("Croatian"), tr("Haitian Creole"), tr("Hungarian"), tr("Armenian"), tr("Indonesian"), tr("Igbo"),
                                                        tr("Icelandic"), tr("Italian"), tr("Japanese"), tr("Javanese"), tr("Georgian"), tr("Kazakh"), tr("Khmer"),
                                                        tr("Kannada"), tr("Korean"), tr("Kurdish"), tr("Kyrgyz"), tr("Latin"), tr("Luxembourgish"), tr("Lao"),
                                                        tr("Lithuanian"), tr("Latvian"), tr("Malagasy"), tr("Maori"), tr("Macedonian"), tr("Malayalam"), tr("Mongolian"),
                                                        tr("Marathi"), tr("Malay"), tr("Maltese"), tr("Hmong Daw"), tr("Myanmar"), tr("Nepali"), tr("Dutch"),
                                                        tr("Norwegian"), tr("Chichewa"), tr("Querétaro Otomi"), tr("Punjabi"), tr("Polish"), tr("Pashto"), tr("Portuguese"),
                                                        tr("Romanian"), tr("Russian"), tr("Sindhi"), tr("Sinhala"), tr("Slovak"), tr("Slovenian"), tr("Samoan"), tr("Shona"),
                                                        tr("Somali"), tr("Albanian"), tr("Serbian"), tr("Sesotho"), tr("Sundanese"), tr("Swedish"), tr("Swahili"),
                                                        tr("Tamil"), tr("Telugu"), tr("Tajik"), tr("Thai"), tr("Filipino"), tr("Klingon"), tr("Klingon (pIqaD)"),
                                                        tr("Tongan"), tr("Turkish"), tr("Tatar"), tr("Tahitian"), tr("Udmurt"), tr("Ukrainian"), tr("Urdu"), tr("Uzbek"),
                                                        tr("Vietnamese"), tr("Xhosa"), tr("Yiddish"), tr("Yoruba"), tr("Yucatec Maya"), tr("Cantonese"),
                                                        tr("Chinese Simplified"), tr("Chinese Traditional"), tr("Zulu") };

const QStringList QOnlineTranslator::LANGUAGE_CODES = { "auto", "af", "am", "ar", "az", "be", "bg", "bn", "bs", "ca", "ceb", "co", "cs", "cy", "da", "de", "el", "en", "eo", "es",
                                                              "et", "eu", "fa", "fi", "fj", "fr", "fy", "ga", "gd", "gl", "gu", "ha", "haw", "he", "hi", "hmn", "hr", "ht", "hu",
                                                              "hy", "id", "ig", "is", "it", "ja", "jv", "ka", "kk", "km", "kn", "ko", "ku", "ky", "la", "lb", "lo", "lt", "lv",
                                                              "mg", "mi", "mk", "ml", "mn", "mr", "ms", "mt", "mww", "my", "ne", "nl", "no", "ny", "otq", "pa", "pl", "ps", "pt",
                                                              "ro", "ru", "sd", "si", "sk", "sl", "sm", "sn", "so", "sq", "sr", "st", "su", "sv", "sw", "ta",
                                                              "te", "tg", "th", "tl", "tlh", "tlh-qaak", "to", "tr", "tt", "ty", "udm", "uk", "ur", "uz", "vi", "xh", "yi", "yo",
                                                              "yua", "yue", "zh-cn", "zh-tw", "zu" };

QOnlineTranslator::QOnlineTranslator(QObject *parent) :
    QObject(parent)
{}

QOnlineTranslator::QOnlineTranslator(const QString &text, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguage, const bool &autoCorrect, QObject *parent) :
    QObject(parent)
{
    translate(text, translationLanguage, sourceLanguage, translatorLanguage, autoCorrect);
}

void QOnlineTranslator::translate(const QString &text, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguage, const bool &autoCorrect)
{
    m_source = text;

    // Detect system language if translateLanguage not specified
    if (translationLanguage == "auto")
        m_translationLanguage = defaultLocaleToCode();
    else
        m_translationLanguage = translationLanguage;

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
    m_sourceLanguage.clear();
    m_options.clear();
    m_error = false;

    // Google has a limit of up to 5000 characters per request. If the query is larger, then it should be splited into several
    QString untranslatedText = text;
    while (!untranslatedText.isEmpty()) {
        int splitIndex = getSplitIndex(untranslatedText); // Split the part by special symbol
        if (splitIndex == -1) {
            // Do not translate the part if it looks like garbage
            m_translation.append(untranslatedText.left(5000));
            untranslatedText = untranslatedText.mid(5000);
            continue;
        }

        // Generate API url
        QUrl apiUrl("https://translate.googleapis.com/translate_a/single");
        apiUrl.setQuery("client=gtx&ie=UTF-8&oe=UTF-8&dt=bd&dt=ex&dt=ld&dt=md&dt=rw&dt=rm&dt=ss&dt=t&dt=at&dt=" + autocorrection +"&sl=" + sourceLanguage + "&tl=" +
                        translationLanguage + "&hl=" + translatorLanguage + "&q=" + QUrl::toPercentEncoding(untranslatedText.left(splitIndex)));

        // Send request
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(apiUrl));

        // Wait for the response
        QEventLoop event;
        QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
        event.exec();

        // Check for network error
        if (reply->error() != QNetworkReply::NoError) {
            m_error = true;
            m_translation = reply->errorString();
            return;
        }

        // Convert to JsonArray
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonArray jsonData = jsonResponse.array();

        // Parse first sentense. If the answer contains more than one sentence, then at the end of the first one there will be a space
        m_translation.append(jsonData.at(0).toArray().at(0).toArray().at(0).toString());
        for (int i = 1; m_translation.endsWith(" ") || m_translation.endsWith("\n") || m_translation.endsWith("\u00a0"); i++)
            m_translation.append(jsonData.at(0).toArray().at(i).toArray().at(0).toString());

        // Parse transcriptions and source language
        m_translationTranscription.append(jsonData.at(0).toArray().last().toArray().at(2).toString());
        m_sourceTranscription.append(jsonData.at(0).toArray().last().toArray().at(3).toString());
        if (m_sourceLanguage.isEmpty())
            m_sourceLanguage = jsonData.at(2).toString();

        // Remove the parsed part from the next parsing
        untranslatedText = untranslatedText.mid(splitIndex);

        // Add a space between parts
        if (!untranslatedText.isEmpty() && !m_translation.endsWith("\n")) {
            m_translation.append(" ");
            m_translationTranscription.append(" ");
            m_sourceTranscription.append(" ");
        }

        // Translation options
        if (text.size() < 5000) {
            foreach (QJsonValue typeOfSpeach, jsonData.at(1).toArray()) {
                m_options.append(QPair<QString, QStringList>());
                m_options.last().first = typeOfSpeach.toArray().at(0).toString();
                foreach (QJsonValue translationOption, typeOfSpeach.toArray().at(2).toArray()) {
                    m_options.last().second.append(translationOption.toArray().at(0).toString() + ": ");
                    // Add the first word without ",", and then add the remaining words
                    m_options.last().second.last().append(translationOption.toArray().at(1).toArray().at(0).toString());
                    for (int i = 1; i < translationOption.toArray().at(1).toArray().size(); i++)
                        m_options.last().second.last().append(", " + translationOption.toArray().at(1).toArray().at(i).toString());
                }
            }
        }
    }
}

QList<QMediaContent> QOnlineTranslator::sourceMedia()
{
    QList<QMediaContent> mediaList;

    // Google has a limit of up to 5000 characters per request. If the query is larger, then it should be splited into several
    QString unparsedText = m_source;
    while (!unparsedText.isEmpty()) {
        int splitIndex = getSplitIndex(unparsedText); // Split the part by special symbol

        // Generate URL API for add it to the playlist
        QUrl apiUrl("http://translate.googleapis.com/translate_tts");
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + m_sourceLanguage +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)));
        mediaList.append(apiUrl);

        // Remove the said part from the next saying
        unparsedText = unparsedText.mid(splitIndex);
    }
    return mediaList;
}

QList<QMediaContent> QOnlineTranslator::translationMedia()
{
    QList<QMediaContent> mediaList;

    // Google has a limit of up to 5000 characters per request. If the query is larger, then it should be splited into several
    QString unparsedText = m_translation;
    while (!unparsedText.isEmpty()) {
        int splitIndex = getSplitIndex(unparsedText); // Split the part by special symbol

        // Generate URL API for add it to the playlist
        QUrl apiUrl("http://translate.googleapis.com/translate_tts");
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + m_translationLanguage +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)));
        mediaList.append(apiUrl);

        // Remove the said part from the next saying
        unparsedText = unparsedText.mid(splitIndex);
    }
    return mediaList;
}

QString QOnlineTranslator::translateText(const QString &text, QString translationLanguage, QString sourceLanguage)
{
    // Detect system language if translationLanguage not specified
    if (translationLanguage == "auto")
        translationLanguage = defaultLocaleToCode();

    QString untranslatedText = text;
    QString translatedText;

    // Google has a limit of up to 5000 characters per request. If the query is larger, then it should be splited into several
    while (!untranslatedText.isEmpty()) {
        int splitIndex = getSplitIndex(untranslatedText); // Split part by special symbols
        if (splitIndex == -1) {
            // Do not translate the part if it looks like garbage
            translatedText.append(untranslatedText.left(5000));
            untranslatedText = untranslatedText.mid(5000);
            continue;
        }

        // Generate short URL API only for translation and and receive a reply
        QUrl apiUrl("https://translate.googleapis.com/translate_a/single");
        apiUrl.setQuery("client=gtx&sl=" + sourceLanguage +"&tl=" + translationLanguage + "&dt=t&q=" + QUrl::toPercentEncoding(untranslatedText.left(splitIndex)));

        // Send request
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(apiUrl));

        // Wait for the response
        QEventLoop event;
        QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
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

QString QOnlineTranslator::codeToLanguage(const QString &code)
{
    int index = LANGUAGE_CODES.indexOf(code);
    return LANGUAGE_NAMES.at(index);
}

QString QOnlineTranslator::languageToCode(const QString &language)
{
    int index = LANGUAGE_NAMES.indexOf(language);
    return LANGUAGE_CODES.at(index);
}

QString QOnlineTranslator::defaultLocaleToCode()
{
    QLocale locale;
    return locale.name().left(locale.name().indexOf("_"));
}

QList<QMediaContent> QOnlineTranslator::media(const QString &text, QString language)
{
    QList<QMediaContent> mediaList;

    // Google don't support "auto" as argument for text-to-speech, so need to detect language manually from translation request
    if (language == "auto") {
        QUrl languageUrl("https://translate.googleapis.com/translate_a/single");
        languageUrl.setQuery("client=gtx&sl=auto&tl=en&dt=t&q=" + QUrl::toPercentEncoding(text.left(getSplitIndex(text))));

        // Send request
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(languageUrl));

        // Wait for the response
        QEventLoop event;
        QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
        event.exec();

        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            return mediaList;
        }

        // Parse language
        language = reply->readAll();
        language.chop(4);
        language = language.mid(language.lastIndexOf("\"") + 1);
    }

    // Google has a limit of up to 5000 characters per request. If the query is larger, then it should be splited into several
    QString unparsedText = text;
    while (!unparsedText.isEmpty()) {
        int splitIndex = getSplitIndex(unparsedText); // Split the part by special symbol

        // Generate URL API for add it to the playlist
        QUrl apiUrl("http://translate.googleapis.com/translate_tts");
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + language +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)));
        mediaList.append(apiUrl);

        // Remove the said part from the next saying
        unparsedText = unparsedText.mid(splitIndex);
    }
    return mediaList;
}

// Split the first part of the 5000 characters by last special symbol
int QOnlineTranslator::getSplitIndex(const QString &untranslatedText)
{
    if (untranslatedText.size() < 5000)
        return 5000;

    int splitIndex = untranslatedText.lastIndexOf(". ", 4999);
    if (splitIndex != -1)
        return splitIndex + 1;

    splitIndex = untranslatedText.lastIndexOf(" ", 4999);
    if (splitIndex != -1)
        return splitIndex + 1;

    splitIndex = untranslatedText.lastIndexOf("\n", 4999);
    if (splitIndex != -1)
        return splitIndex + 1;

    // Non-breaking gap
    splitIndex = untranslatedText.lastIndexOf("\u00a0", 4999);
    if (splitIndex != -1)
        return splitIndex + 1;
    else
        return 5000;
}
